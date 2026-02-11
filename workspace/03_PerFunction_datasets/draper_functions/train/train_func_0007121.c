goo_canvas_svg_finalize (GObject *object)
{
  GooCanvasSvg *canvas_svg = (GooCanvasSvg*) object;

  if (canvas_svg->id)
    g_free(canvas_svg->id);
  canvas_svg->id = NULL;

  if (canvas_svg->pattern)
      cairo_pattern_destroy(canvas_svg->pattern);
  canvas_svg->pattern = NULL;

  if (canvas_svg->cr)
    cairo_destroy(canvas_svg->cr);
  canvas_svg->cr = NULL;

  if (canvas_svg->svg_handle)
    g_object_unref (canvas_svg->svg_handle);
  canvas_svg->svg_handle = NULL;

  G_OBJECT_CLASS (goo_canvas_svg_parent_class)->finalize (object);
}
