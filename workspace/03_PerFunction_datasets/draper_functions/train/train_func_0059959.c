gt_canvas_cairo_file_to_file(GtCanvasCairoFile *canvas,
                                 const char *filename, GtError *err)
{
  int had_err = 0;
  GtCanvas *c = (GtCanvas*) canvas;
  gt_error_check(err);
  gt_assert(canvas && filename);

  if (c->pvt->g)
    had_err = gt_graphics_save_to_file(c->pvt->g, filename, err);
  else
  {

    gt_error_set(err, "No graphics has been created yet!");
    had_err = -1;
  }

  return had_err;
}
