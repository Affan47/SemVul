art_render_svp_callback_opacity (void *callback_data, int y,
				 int start, ArtSVPRenderAAStep *steps, int n_steps)
{
  ArtMaskSourceSVP *z = (ArtMaskSourceSVP *)callback_data;
  ArtRender *render = z->render;
  int n_run = 0;
  int i;
  art_u32 running_sum;
  int x0 = render->x0;
  int x1 = render->x1;
  int run_x0, run_x1;
  ArtRenderMaskRun *run = render->run;
  art_u32 opacity = render->opacity;
  art_u32 alpha;

  running_sum = start - 0x7f80;

  if (n_steps > 0)
    {
      run_x1 = steps[0].x;
      alpha = ((running_sum >> 8) * opacity + 0x80080) >> 8;
      if (run_x1 > x0 && alpha > 0x80ff)
	{
	  run[0].x = x0;
	  run[0].alpha = alpha;
	  n_run++;
	}

      for (i = 0; i < n_steps - 1; i++)
	{
          running_sum += steps[i].delta;
          run_x0 = run_x1;
          run_x1 = steps[i + 1].x;
	  if (run_x1 > run_x0)
	    {
	      run[n_run].x = run_x0;
	      alpha = ((running_sum >> 8) * opacity + 0x80080) >> 8;
	      run[n_run].alpha = alpha;
	      n_run++;
	    }
	}
      if (x1 > run_x1)
	{
	  running_sum += steps[n_steps - 1].delta;
	  run[n_run].x = run_x1;
	  alpha = ((running_sum >> 8) * opacity + 0x80080) >> 8;
	  run[n_run].alpha = alpha;
	  n_run++;
	}
      if (alpha > 0x80ff)
	{
	  run[n_run].x = x1;
	  run[n_run].alpha = 0x8000;
	  n_run++;
	}
    }
  else if ((running_sum >> 16) > 0)
    {
      run[0].x = x0;
      run[0].alpha = running_sum;
      run[1].x = x1;
      run[1].alpha = running_sum;
      n_run = 2;
    }

  render->n_run = n_run;

  art_render_invoke_callbacks (render, z->dest_ptr, y);

  z->dest_ptr += render->rowstride;
}
