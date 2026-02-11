gst_rsvg_overlay_data_sink_event (GstPad * pad, GstEvent * event)
{
  GstRsvgOverlay *overlay = GST_RSVG_OVERLAY (GST_PAD_PARENT (pad));

  GST_LOG_OBJECT (pad, "Got %s event", GST_EVENT_TYPE_NAME (event));

  switch (GST_EVENT_TYPE (event)) {

    case GST_EVENT_EOS:{
      guint data_size;

      GST_RSVG_LOCK (overlay);


      data_size = gst_adapter_available (overlay->adapter);
      if (data_size) {
        gst_rsvg_overlay_set_svg_data (overlay,
            (const gchar *) gst_adapter_take (overlay->adapter, data_size),
            FALSE);
        gst_adapter_clear (overlay->adapter);
      }
      GST_RSVG_UNLOCK (overlay);
    }

    case GST_EVENT_FLUSH_START:
      gst_adapter_clear (overlay->adapter);
      break;

    default:
      break;
  }


  gst_event_unref (event);
  return TRUE;
}
