gst_avi_mux_release_pad (GstElement * element, GstPad * pad)
{
  GstAviMux *avimux = GST_AVI_MUX (element);
  GSList *node;

  node = avimux->sinkpads;
  while (node) {
    GstAviPad *avipad = (GstAviPad *) node->data;

    if (avipad->collect->pad == pad) {


      avipad->collect = NULL;
      GST_DEBUG_OBJECT (avimux, "removed pad '%s'", GST_PAD_NAME (pad));
      gst_collect_pads_remove_pad (avimux->collect, pad);
      gst_element_remove_pad (element, pad);


      if (avimux->write_header) {
        avimux->sinkpads = g_slist_remove (avimux->sinkpads, avipad);
        gst_avi_mux_pad_reset (avipad, TRUE);
        g_free (avipad);
      }
      return;
    }

    node = node->next;
  }

  g_warning ("Unknown pad %s", GST_PAD_NAME (pad));
}
