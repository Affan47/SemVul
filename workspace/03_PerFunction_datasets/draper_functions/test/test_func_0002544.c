doDrawBitmap(Bitmap bitmap)
{

#if 1


  if (!bitmap.renderData()) {
    RenderData *render = new RenderData;
    render->pixels = bitmap.pixelData();

    bitmap.setRenderData(render);
  }
  if (!bitmap.renderData())
    return;
  RenderData *render = static_cast<RenderData *>(bitmap.renderData());
  Buffer data = render->pixels;
#else
  Buffer data = bitmap.pixelData();
#endif
  if (!data.size())
    return;

  cairo_surface_t *image =
    cairo_image_surface_create_for_data((uchar *) data.data(),
					CAIRO_FORMAT_ARGB32,
					bitmap.width(), bitmap.height(),
					4 * bitmap.width());
  cairo_save(iCairo);
  Matrix tf = matrix() * Matrix(1.0 / bitmap.width(), 0.0,
				0.0, -1.0 / bitmap.height(),
				0.0, 1.0);
  cairo_matrix_t matrix;
  matrix.xx = tf.a[0];
  matrix.yx = tf.a[1];
  matrix.xy = tf.a[2];
  matrix.yy = tf.a[3];
  matrix.x0 = tf.a[4];
  matrix.y0 = tf.a[5];
  cairo_transform(iCairo, &matrix);
  cairo_set_source_surface(iCairo, image, 0, 0);
  cairo_pattern_set_filter(cairo_get_source(iCairo), CAIRO_FILTER_NEAREST);
  cairo_paint(iCairo);
  cairo_restore(iCairo);
}
