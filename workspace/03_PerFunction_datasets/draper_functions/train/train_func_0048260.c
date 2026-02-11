curve_editor_finalize (GObject *object)
{
  CurveEditor *curve;

  g_return_if_fail (IS_CURVE_EDITOR (object));

  curve = CURVE_EDITOR(object);
  if (curve->pixmap)
    g_object_unref (curve->pixmap);
  if (curve->point)
    g_free (curve->point);
  if (curve->spline.points)
    g_free (curve->spline.points);

  G_OBJECT_CLASS (parent_class)->finalize (object);
}
