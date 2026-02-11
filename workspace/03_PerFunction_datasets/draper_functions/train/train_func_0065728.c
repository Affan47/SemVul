fillToStrokePathClip(GfxState *state) {
  cairo_save (cairo);

  cairo_set_matrix (cairo, &strokePathClip->ctm);
  cairo_set_line_width (cairo, strokePathClip->line_width);
  strokePathClip->dash_count = cairo_get_dash_count (cairo);
  cairo_set_dash (cairo, strokePathClip->dashes, strokePathClip->dash_count, strokePathClip->dash_offset);
  cairo_set_line_cap (cairo, strokePathClip->cap);
  cairo_set_line_join (cairo, strokePathClip->join);
  cairo_set_miter_limit (cairo, strokePathClip->miter);
  doPath (cairo, state, strokePathClip->path);
  cairo_stroke (cairo);

  cairo_restore (cairo);

  delete strokePathClip->path;
  if (strokePathClip->dashes)
    gfree (strokePathClip->dashes);
  gfree (strokePathClip);
  strokePathClip = NULL;
}
