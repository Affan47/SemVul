cat_tail_grep_shot_i_draw(tenm_object *my, int priority)
{
  int status = 0;
  tenm_color color;


  if (my == NULL)
  {
    fprintf(stderr, "cat_tail_grep_shot_i_draw: my is NULL\n");
    return 0;
  }


  if (priority != 1)
    return 0;

  color = tenm_map_color(75, 0, 239);

  if (tenm_draw_circle((int) (my->x), (int) (my->y), 5, 2, color) != 0)
    status = 1;

  return status;
}
