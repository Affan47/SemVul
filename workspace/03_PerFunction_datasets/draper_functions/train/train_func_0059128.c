gst_auto_convert_get_internal_sinkpad (GstAutoConvert * autoconvert)
{
  GstPad *pad = NULL;

  GST_AUTOCONVERT_LOCK (autoconvert);
  if (autoconvert->current_internal_sinkpad)
    pad = gst_object_ref (autoconvert->current_internal_sinkpad);
  GST_AUTOCONVERT_UNLOCK (autoconvert);

  return pad;
}
