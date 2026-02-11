updateFillColorStop(GfxState *state, double offset) {
  if (inUncoloredPattern)
    return;

  state->getFillRGB(&fill_color);

  cairo_pattern_add_color_stop_rgba(fill_pattern, offset,
				    colToDbl(fill_color.r),
				    colToDbl(fill_color.g),
				    colToDbl(fill_color.b),
				    fill_opacity);
  LOG(printf ("fill color stop: %f (%d, %d, %d)\n",
	      offset, fill_color.r, fill_color.g, fill_color.b));
}
