gst_output_selector_release_pad (GstElement * element, GstPad * pad)
{
  GstOutputSelector *osel;

  osel = GST_OUTPUT_SELECTOR (element);

  GST_DEBUG_OBJECT (osel, "releasing pad");

  gst_pad_set_active (pad, FALSE);

  gst_element_remove_pad (GST_ELEMENT_CAST (osel), pad);
}
