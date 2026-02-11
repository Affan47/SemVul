create_source (void)
{
  int x, y;
  ClutterActor *group = clutter_group_new ();


  for (y = 0; y < SOURCE_DIVISIONS_Y; y++)
    for (x = 0; x < SOURCE_DIVISIONS_X; x++)
      {
        ClutterActor *rect = clutter_rectangle_new ();
        clutter_actor_set_size (rect, DIVISION_WIDTH, DIVISION_HEIGHT);
        clutter_actor_set_position (rect,
                                    DIVISION_WIDTH * x,
                                    DIVISION_HEIGHT * y);
        clutter_rectangle_set_color (CLUTTER_RECTANGLE (rect),
                                     corner_colors +
                                     (y * SOURCE_DIVISIONS_X + x));
        clutter_container_add (CLUTTER_CONTAINER (group), rect, NULL);
      }

  return group;
}
