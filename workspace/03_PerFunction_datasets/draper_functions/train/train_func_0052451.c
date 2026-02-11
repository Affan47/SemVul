update(sprite_t *s)
{
  float v[2],x,pull[2];
  mech_sprite_t *ms = (mech_sprite_t *)s;

  sprite_get_vel(s,v);
  if (!(s->state & BIPLANE_CRASHING))
    {
      if (s->state & BIPLANE_ACCELERATING)
	{
	  vset(pull,mech_heading(ms));
	  vrot(pull,-16);
	  vmadd(ms->lin_impulse,engine_strength,pull);
	}
      if (s->state & BIPLANE_UP)
	ms->air_rotate = -turn_amount;
      else if (s->state & BIPLANE_DOWN)
	ms->air_rotate = turn_amount;
      else
	ms->air_rotate = 0;

      if (ms->damage >= hitpoints)
	{
	  s->state |= BIPLANE_CRASHING;
	  sprite_set_animation(s,crashing);
	  create_effect(&fire,s->x,s->y);
	  sprite_alarm(7000,s,SIGNAL_KILL,0);
	}
    }
  mech_update(ms);
}
