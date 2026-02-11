validate_part (TestState *state,
               int xpos, int ypos,
               int clip_flags)
{
  int x, y;


  for (y = 0; y < SOURCE_DIVISIONS_Y; y++)
    for (x = 0; x < SOURCE_DIVISIONS_X; x++)
      {
        guchar *pixels;
        const ClutterColor *correct_color;


        pixels = clutter_stage_read_pixels (CLUTTER_STAGE (state->stage),
                                            x * DIVISION_WIDTH +
                                            DIVISION_WIDTH / 2 + xpos,
                                            y * DIVISION_HEIGHT +
                                            DIVISION_HEIGHT / 2 + ypos,
                                            1, 1);


        if ((clip_flags & (1 << ((y * SOURCE_DIVISIONS_X) + x))))
          correct_color = &stage_color;
        else

          correct_color = corner_colors + (y * SOURCE_DIVISIONS_X) + x;

        g_assert (pixels != NULL);
        g_assert_cmpint (pixels[0], ==, correct_color->red);
        g_assert_cmpint (pixels[1], ==, correct_color->green);
        g_assert_cmpint (pixels[2], ==, correct_color->blue);

        g_free (pixels);
      }
}
