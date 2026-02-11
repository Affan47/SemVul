test_shoving_into_region ()
{
  GList* region;
  MetaRectangle rect, temp;
  FixedDirections fixed_directions = 0;
  int i;

  region = get_screen_region (3);
  for (i = 0; i < NUM_RANDOM_RUNS; i++)
    {
      get_random_rect (&rect);
      if (meta_rectangle_could_fit_in_region (region, &rect))
        {
          meta_rectangle_shove_into_region (region, 0, &rect);
          g_assert (meta_rectangle_contained_in_region (region, &rect));
        }
    }
  meta_rectangle_free_list_and_elements (region);


  region = get_screen_region (2);

  rect = meta_rect (300, 1000, 400, 200);
  temp = meta_rect (300,  950, 400, 200);
  meta_rectangle_shove_into_region (region,
                                    fixed_directions,
                                    &rect);
  g_assert (meta_rectangle_equal (&rect, &temp));

  rect = meta_rect (425, 1000, 300, 200);
  temp = meta_rect (450, 1000, 300, 200);
  meta_rectangle_shove_into_region (region,
                                    fixed_directions,
                                    &rect);
  g_assert (meta_rectangle_equal (&rect, &temp));

  rect = meta_rect (425, 1000, 300, 200);
  temp = meta_rect (425,  950, 300, 200);
  meta_rectangle_shove_into_region (region,
                                    FIXED_DIRECTION_X,
                                    &rect);
  g_assert (meta_rectangle_equal (&rect, &temp));

  rect = meta_rect ( 300, 1000, 400, 200);
  temp = meta_rect (1200, 1000, 400, 200);
  meta_rectangle_shove_into_region (region,
                                    FIXED_DIRECTION_Y,
                                    &rect);
  g_assert (meta_rectangle_equal (&rect, &temp));

  rect = meta_rect ( 800, 1150, 400,  50);
  temp = meta_rect ( 800, 1050, 400,  50);
  meta_rectangle_shove_into_region (region,
                                    0,
                                    &rect);
  g_assert (meta_rectangle_equal (&rect, &temp));

  rect = meta_rect (-1000,  0, 400, 150);
  temp = meta_rect (    0, 20, 400, 150);
  meta_rectangle_shove_into_region (region,
                                    0,
                                    &rect);
  g_assert (meta_rectangle_equal (&rect, &temp));

  meta_rectangle_free_list_and_elements (region);

  printf ("%s passed.\n", G_STRFUNC);
}
