mx_grid_get_preferred_height (ClutterActor *self,
                              gfloat        for_width,
                              gfloat       *min_height_p,
                              gfloat       *natural_height_p)
{
  gfloat actual_height, min_height;
  ClutterActorBox box;

  box.x1 = 0;
  box.y1 = 0;
  box.x2 = for_width;
  box.y2 = G_MAXFLOAT;

  mx_grid_do_allocate (self, &box, FALSE,
                       TRUE, NULL, &actual_height, NULL, &min_height);

  if (min_height_p)
    *min_height_p = min_height;
  if (natural_height_p)
    *natural_height_p = actual_height;
}
