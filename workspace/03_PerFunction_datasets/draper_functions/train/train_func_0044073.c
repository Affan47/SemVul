do_propagate(GArray *foreground_samples, GArray *background_samples, gfloat *input, gfloat *output, guchar *trimap, int x, int y, int w, int h) {
  int index_orig = y * w + x;
  int index_new;

  if (!(trimap[index_orig] == 0 || trimap[index_orig] == 255))
    {
      int xdiff, ydiff;
      float best_cost = FLT_MAX;
      float *best_fg_distance = &output[index_orig * 4 + 0];
      float *best_bg_distance = &output[index_orig * 4 + 1];

      for (ydiff = -1; ydiff <= 1; ydiff++)
        {

          if (y+ydiff < 0 || y+ydiff >= h)
            continue;
          for (xdiff = -1; xdiff <= 1; xdiff++)
            {

              if (x+xdiff < 0 || x+xdiff >= w)
                continue;

              index_new = (y + ydiff) * w + (x + xdiff);

              if (!(trimap[index_new] == 0 || trimap[index_new] == 255))
                {
                  int fi = FG_INDEX(output, index_new);
                  int bi = BG_INDEX(output, index_new);

                  ColorSample foreground = g_array_index(foreground_samples, ColorSample, fi);
                  ColorSample background = g_array_index(background_samples, ColorSample, bi);

                  float cost = get_cost(foreground, background, &input[index_orig * 3], x, y, best_fg_distance, best_bg_distance);
                  if (cost < best_cost)
                    {
                      FG_INDEX(output, index_orig) = fi;
                      BG_INDEX(output, index_orig) = bi;
                      best_cost = cost;
                    }
                }
            }
        }
    }
}
