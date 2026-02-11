art_rgb_svp_alpha_callback (void *callback_data, int y,
			    int start, ArtSVPRenderAAStep *steps, int n_steps)
{
  ArtRgbSVPAlphaData *data = (ArtRgbSVPAlphaData *)callback_data;
  art_u8 *linebuf;
  int run_x0, run_x1;
  art_u32 running_sum = start;
  int x0, x1;
  int k;
  art_u8 r, g, b;
  int *alphatab;
  int alpha;

  linebuf = data->buf;
  x0 = data->x0;
  x1 = data->x1;

  r = data->r;
  g = data->g;
  b = data->b;
  alphatab = data->alphatab;

  if (n_steps > 0)
    {
      run_x1 = steps[0].x;
      if (run_x1 > x0)
	{
	  alpha = (running_sum >> 16) & 0xff;
	  if (alpha)
	    art_rgb_run_alpha (linebuf,
			       r, g, b, alphatab[alpha],
			       run_x1 - x0);
	}

      for (k = 0; k < n_steps - 1; k++)
	{
	  running_sum += steps[k].delta;
	  run_x0 = run_x1;
	  run_x1 = steps[k + 1].x;
	  if (run_x1 > run_x0)
	    {
	      alpha = (running_sum >> 16) & 0xff;
	      if (alpha)
		art_rgb_run_alpha (linebuf + (run_x0 - x0) * 3,
				   r, g, b, alphatab[alpha],
				   run_x1 - run_x0);
	    }
	}
      running_sum += steps[k].delta;
      if (x1 > run_x1)
	{
	  alpha = (running_sum >> 16) & 0xff;
	  if (alpha)
	    art_rgb_run_alpha (linebuf + (run_x1 - x0) * 3,
			       r, g, b, alphatab[alpha],
			       x1 - run_x1);
	}
    }
  else
    {
      alpha = (running_sum >> 16) & 0xff;
      if (alpha)
	art_rgb_run_alpha (linebuf,
			   r, g, b, alphatab[alpha],
			   x1 - x0);
    }

  data->buf += data->rowstride;
}
