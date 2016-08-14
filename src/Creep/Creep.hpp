#pragma once

#ifndef TDF_CREEP_HPP
#define TDF_CREEP_HPP

#include <memory>
#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>
#include "../Renderable.hpp"
#include "CreepDisplayComponent.hpp"
#include "CreepWalkComponent.hpp"

//! \brief Represents an enemy in the level.
//! A Creep is composed of two components: walking and display.
//! Besides forwarding some methods to the components, it also keeps
//! track of the Creep's life.
class Creep : public Renderable
{
private:
	std::unique_ptr<CreepWalkComponent> walkComponent_;
	std::unique_ptr<CreepDisplayComponent> displayComponent_;
	int32_t life_, maxLife_;
	int32_t bounty_;

public:
	Creep(int32_t maxLife, int32_t bounty,
		std::unique_ptr<CreepWalkComponent> walkComponent,
		std::unique_ptr<CreepDisplayComponent> displayComponent);

	inline void update(NavigationProvider<sf::Vector2i> & navigation)
	{
		walkComponent_->update(navigation);
	}

	inline virtual void render(sf::RenderTarget & target) override
	{
		displayComponent_->render(target);
	}

	inline sf::Vector2f getPosition() const
	{
		return walkComponent_->getPosition();
	}

	inline bool isAlive() const
	{
		return life_ > 0;
	}

	inline int32_t getLife() const
	{
		return life_;
	}

	inline int32_t getMaxLife() const
	{
		return maxLife_;
	}

	inline bool hasReachedGoal() const
	{
		return walkComponent_->hasReachedGoal();
	}

	inline void inflictDamage(int32_t damage)
	{
		life_ -= damage;
	}

	inline int32_t getBounty() const
	{
		return bounty_;
	}
};

#endif // TDF_CREEP_HPP