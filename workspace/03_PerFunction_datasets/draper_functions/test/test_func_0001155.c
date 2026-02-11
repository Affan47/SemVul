gst_decode_pad_set_blocked (GstDecodePad * dpad, gboolean blocked)
{
  GstDecodeBin *dbin = dpad->dbin;
  GstPad *opad;

  DYN_LOCK (dbin);

  GST_DEBUG_OBJECT (dpad, "blocking pad: %d", blocked);

  opad = gst_ghost_pad_get_target (GST_GHOST_PAD_CAST (dpad));
  if (!opad)
    goto out;


  if (!blocked || !dbin->shutdown) {
    if (blocked) {
      if (dpad->block_id == 0)
        dpad->block_id =
            gst_pad_add_probe (opad,
            GST_PAD_PROBE_TYPE_BLOCK_DOWNSTREAM |
            GST_PAD_PROBE_TYPE_QUERY_DOWNSTREAM, source_pad_blocked_cb,
            gst_object_ref (dpad), (GDestroyNotify) gst_object_unref);
    } else {
      if (dpad->block_id != 0) {
        gst_pad_remove_probe (opad, dpad->block_id);
        dpad->block_id = 0;
      }
      dpad->blocked = FALSE;
    }
  }

  if (blocked) {
    if (dbin->shutdown) {

      gst_pad_set_active (GST_PAD_CAST (dpad), FALSE);


    } else {
      gst_object_ref (dpad);
      dbin->blocked_pads = g_list_prepend (dbin->blocked_pads, dpad);
    }
  } else {
    GList *l;

    if ((l = g_list_find (dbin->blocked_pads, dpad))) {
      gst_object_unref (dpad);
      dbin->blocked_pads = g_list_delete_link (dbin->blocked_pads, l);
    }
  }
  gst_object_unref (opad);
out:
  DYN_UNLOCK (dbin);
}
