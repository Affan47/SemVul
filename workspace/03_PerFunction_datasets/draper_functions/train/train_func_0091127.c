dynamic_add (GstElement * element, GstPad * pad, GstDecodeBin * decode_bin)
{
  GstDynamic *dyn;
  struct DynFind find_info;
  GList *found;

  g_return_if_fail (element != NULL);


  find_info.elem = element;
  find_info.pad = pad;
  found = g_list_find_custom (decode_bin->dynamics, &find_info,
      (GCompareFunc) find_dynamic);
  if (found != NULL)
    goto exit;


  dyn = g_new0 (GstDynamic, 1);
  dyn->element = gst_object_ref (element);
  dyn->decode_bin = gst_object_ref (decode_bin);
  if (pad) {
    dyn->pad = gst_object_ref (pad);
    GST_DEBUG_OBJECT (decode_bin, "dynamic create for pad %" GST_PTR_FORMAT,
        pad);
    dyn->caps_sig_id = g_signal_connect (G_OBJECT (pad), "notify::caps",
        G_CALLBACK (new_caps), dyn);
  } else {
    GST_DEBUG_OBJECT (decode_bin, "dynamic create for element %"
        GST_PTR_FORMAT, element);
    dyn->np_sig_id = g_signal_connect (G_OBJECT (element), "pad-added",
        G_CALLBACK (new_pad), dyn);
    dyn->nmp_sig_id = g_signal_connect (G_OBJECT (element), "no-more-pads",
        G_CALLBACK (no_more_pads), dyn);
  }


  decode_bin->dynamics = g_list_prepend (decode_bin->dynamics, dyn);

  return;
exit:
  if (element) {
    GST_DEBUG_OBJECT (decode_bin, "Dynamic element already added: %"
        GST_PTR_FORMAT, element);
  } else {
    GST_DEBUG_OBJECT (decode_bin, "Dynamic pad already added: %"
        GST_PTR_FORMAT, pad);
  }
}
