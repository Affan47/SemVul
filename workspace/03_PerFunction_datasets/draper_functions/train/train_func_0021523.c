net_can_howl_black_hole_new(double x, double y)
{
  tenm_object *new = NULL;
  int *count = NULL;

  count = (int *) malloc(sizeof(int) * 3);
  if (count == NULL)
  {
    fprintf(stderr, "net_can_howl_black_hole_new: malloc(count) failed\n");
    return NULL;
  }


  count[0] = 6;
  count[1] = 1;
  count[2] = 0;


  new = tenm_object_new("net can howl black-hole", ATTR_ENEMY_SHOT, 0,
                        0, x, y,
                        3, count, 0, NULL, 0, NULL,
                        (int (*)(tenm_object *, double)) NULL,
                        (int (*)(tenm_object *, tenm_object *))
                        NULL,
                        (int (*)(tenm_object *, const tenm_object *))
                        (&net_can_howl_black_hole_act),
                        (int (*)(tenm_object *, int))
                        (&net_can_howl_black_hole_draw));
  if (new == NULL)
  {
    fprintf(stderr, "net_can_howl_black_hole_new: tenm_object_new failed\n");
    if (count != NULL)
      free(count);
    return NULL;
  }

  return new;
}
