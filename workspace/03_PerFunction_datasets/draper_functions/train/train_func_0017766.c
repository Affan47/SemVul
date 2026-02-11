sprite_group_draw(sprite_group_t *group)
{
  int i;
  for (i=0; i < group->nr_sprites; i++)
    {
      animation_draw(group->sprites[i]->animation,
		     group->sprites[i]->x,
		     group->sprites[i]->y,
		     group->sprites[i]->anim_p);
    }
}
