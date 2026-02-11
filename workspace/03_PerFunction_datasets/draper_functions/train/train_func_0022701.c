sprite_group_pos_update(sprite_group_t *group)
{
  int i;
  for (i=0; i < group->nr_sprites; i++)
    {
      group->sprites[i]->x = group->sprites[i]->pos[0] + 0.5;
      group->sprites[i]->y = group->sprites[i]->pos[1] + 0.5;
    }
}
