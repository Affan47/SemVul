ai_update(controller_t *c)
{
  float x,delta[2];
  int i = 0;
  struct ai *ai = (struct ai *)c;
  struct signal_reply r = {0,0};
  if (!sprite_isvalid(&(c->target)))
    {
      sprite_release(&ai->enemy);
      return;
    }
  if (sprite_isvalid(&(ai->enemy)))
    {
      sprite_signal(c->target,SIGNAL_CANCONTROL,&i);
      if (i)
	{

	  sprite_signal(ai->enemy,SIGNAL_ISHARMLESS,&r);
	  if (r.reply)

	    {
	      sprite_release(&(ai->enemy));
	      return;
	    }

	  sprite_signal(c->target,SIGNAL_ACCELERATE,0);

	  delta[0] = c->target->x - ai->enemy->x;
	  delta[1] = c->target->y - ai->enemy->y;
	  if (vcross(delta,
		     mech_heading((mech_sprite_t *)(c->target))) < 0)
	    sprite_signal(c->target,SIGNAL_UP,0);
	  else
	    sprite_signal(c->target,SIGNAL_DOWN,0);


	  x = square(vdot(delta,
		      mech_heading((mech_sprite_t *)(c->target))));
	  if  ((vabs2(delta) < 40000) && (vabs2(delta)*0.8 < x))
	    sprite_signal(c->target,SIGNAL_FIRE,0);
	}
      else
	{
	  sprite_release(&(ai->enemy));
	  sprite_release(&(c->target));
	}
    }
  else
    {
      delta[0] = c->target->x - 400;
      delta[1] = c->target->y - 100;
      sprite_signal(c->target,SIGNAL_ACCELERATE,0);
      if (vcross(delta,
		 mech_heading((mech_sprite_t *)(c->target))) < 0)
	sprite_signal(c->target,SIGNAL_UP,0);
      else
	sprite_signal(c->target,SIGNAL_DOWN,0);
    }
}
