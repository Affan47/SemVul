dyesub_print_row(stp_vars_t *v,
		dyesub_print_vars_t *pv,
		int row,
		int plane)
{
  int ret = 0;
  int w, col;

  for (w = 0; w < pv->outw_px; w++)
    {
      col = dyesub_interpolate(w, pv->outw_px, pv->imgw_px);
      if (pv->plane_lefttoright)
	ret = dyesub_print_pixel(v, pv, row, pv->imgw_px - col - 1, plane);
      else
	ret = dyesub_print_pixel(v, pv, row, col, plane);
      if (ret > 1)
      	break;
    }
  return ret;
}
