activate_pads (const GValue * vpad, GValue * ret, gboolean * active)
{
  GstPad *pad = g_value_get_object (vpad);
  gboolean cont = TRUE;

  if (!(cont = gst_pad_set_active (pad, *active)))
    g_value_set_boolean (ret, FALSE);

  return cont;
}
