normal_shot_new(double x, double y, double speed_x, double speed_y,
                int color, int life, int immortal_time)
{
  tenm_primitive **p = NULL;
  tenm_object *new = NULL;
  int *count = NULL;
  double *count_d = NULL;


  if (life == 0)
  {
    fprintf(stderr, "normal_shot_new: life is 0\n");
    return NULL;
  }

  p = (tenm_primitive **) malloc(sizeof(tenm_primitive *) * 1);
  if (p == NULL)
  {
    fprintf(stderr, "normal_shot_new: malloc(p) failed\n");
    return NULL;
  }

  p[0] = (tenm_primitive *) tenm_circle_new(x, y, 5.0);
  if (p[0] == NULL)
  {
    fprintf(stderr, "normal_shot_new: cannot set p[0]\n");
    free(p);
    return NULL;
  }

  count = (int *) malloc(sizeof(int) * 3);
  if (count == NULL)
  {
    fprintf(stderr, "normal_shot_new: malloc(count) failed\n");
    (p[0])->delete(p[0]);
    free(p);
    return NULL;
  }
  count_d = (double *) malloc(sizeof(double) * 2);
  if (count_d == NULL)
  {
    fprintf(stderr, "normal_shot_new: malloc(count_d) failed\n");
    free(count);
    (p[0])->delete(p[0]);
    free(p);
    return NULL;
  }

  count[0] = color;
  count[1] = life;
  count[2] = immortal_time;

  count_d[0] = speed_x;
  count_d[1] = speed_y;

  new = tenm_object_new("normal shot", ATTR_ENEMY_SHOT, ATTR_OPAQUE,
                        1, x, y,
                        3, count, 2, count_d, 1, p,
                        (int (*)(tenm_object *, double)) (&normal_shot_move),
                        (int (*)(tenm_object *, tenm_object *))
                        (&normal_shot_hit),
                        (int (*)(tenm_object *, const tenm_object *))
                        (&normal_shot_act),
                        (int (*)(tenm_object *, int)) (&normal_shot_draw));
  if (new == NULL)
  {
    fprintf(stderr, "normal_shot_new: tenm_object_new failed\n");
    if (count_d != NULL)
      free(count_d);
    if (count != NULL)
      free(count);
    (p[0])->delete(p[0]);
    free(p);
    return NULL;
  }

  return new;
}
