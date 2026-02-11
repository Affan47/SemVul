collide (DynamicObj *d, Uint32 dt)
{
  if (immunity > 0 || d->immunity > 0) return;
  if (explode > 0 || sink > 0) return;

  bool collide = false;
  if (tl->x + o->cubex >= d->tl->x - d->o->cubex && tl->x - o->cubex <= d->tl->x + d->o->cubex &&
      tl->y + o->cubey >= d->tl->y - d->o->cubey && tl->y - o->cubey <= d->tl->y + d->o->cubey &&
      tl->z + o->cubez >= d->tl->z - d->o->cubez && tl->z - o->cubez <= d->tl->z + d->o->cubez)
  {
    collide = true;
  }

  if (collide)
  {
    if (this == (DynamicObj *) fplayer && game == GAME_PLAY && realism && d->id >= AIR && d->id < MOVING_GROUND)
	  {
      shield = -1.0F;
	    d->shield = -1.0F;
	  }
    if (id < STATIC_PASSIVE || (id >= STATIC_PASSIVE && d->id >= MISSILE1 && d->id <= MISSILE2))
      shield -= (float) d->impact;
    else
      shield -= 2.0F;
    d->shield -= (float) impact;
    if (d->source != NULL && active)
    {
      if (d->source->party != party)
      {
        if (maxshield < 2000)
          d->source->points += (int) impact;
      }
      else
      {
        d->source->points -= (int) impact;
      }

      if (shield <= 0)
        if (d->source->party != party && active && draw && !killed)
          if (d->source->id >= FIGHTER1 && d->source->id <= FIGHTER2)
          {
            killed = true;
            if (id >= FIGHTER1 && id <= FIGHTER2)
              d->source->fighterkills ++;
            else if (id >= SHIP1 && id <= SHIP2)
              d->source->shipkills ++;
            else if ((id >= FLAK1 && id <= FLAK2) || (id >= TANK1 && id <= TANK2))
              d->source->tankkills ++;
            else
              d->source->otherkills ++;
          }
    }
    setExplosion (0.2, 20 * timestep);
    setBlackSmoke (0.5, 30 * timestep);
  }
}
