collide(struct sprite *this_sprite,
		    struct sprite *other_sprite,
		    int x, int y)
{
  if (this_sprite->state == 0)
    {
      this_sprite->state = 1;
      sprite_set_animation(this_sprite, dissolve);
    }
}
