receiveDamage( float amount ) {
  if ( lroundf(shield) >= amount ) {
    shield -= amount;
    shieldDamageActive = true;
    shieldDamageEndTime = SDL_GetTicks() + RACER_SHIELD_DAMAGE_LIFETIME;
    return;
  }
  amount -= shield;
  shield = 0;
  damage -= amount;
}
