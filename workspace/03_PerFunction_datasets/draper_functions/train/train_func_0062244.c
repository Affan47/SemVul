gst_pad_get_pad_template (GstPad * pad)
{
  GstPadTemplate *templ;

  g_return_val_if_fail (GST_IS_PAD (pad), NULL);

  templ = GST_PAD_PAD_TEMPLATE (pad);

  return (templ ? gst_object_ref (templ) : NULL);
}
