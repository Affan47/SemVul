visu_ui_curve_frame_getIntegralInRange(VisuUiCurveFrame *curve, gchar **label)
{
  guint *data;
  float val, d;
  guint i;

  g_return_val_if_fail(VISU_UI_IS_CURVE_FRAME(curve), 0.f);

  if (label && curve->filter)
    *label = curve->filter;
  else if (label)
    *label = ALL;

  if (curve->filter)
    data = (guint*)g_hash_table_lookup(curve->data, curve->filter);
  else
    data = (guint*)g_hash_table_lookup(curve->data, ALL);
  if (!data)
    return 0.f;

  val = 0.f;
  d = curve->init;
  for (i = 0; i < curve->nSteps - 1; i++)
    {
      if (d >= curve->hlRange[0] && d < curve->hlRange[1])
	val += (float)data[i];
      d += curve->step;
    }

  DBG_fprintf(stderr, "Gtk Curve: get %d pairs for %d elements.\n",
	      (int)val, data[curve->nSteps - 1]);
  return val / (float)data[curve->nSteps - 1];
}
