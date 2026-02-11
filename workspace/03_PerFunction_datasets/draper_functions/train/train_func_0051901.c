gst_rfb_src_event (GstBaseSrc * bsrc, GstEvent * event)
{
  GstRfbSrc *src = GST_RFB_SRC (bsrc);
  gdouble x, y;
  gint button;
  const GstStructure *structure;
  const gchar *event_type;
  gboolean key_event, key_press;

  key_event = FALSE;

  switch (GST_EVENT_TYPE (event)) {
    case GST_EVENT_NAVIGATION:


      if (src->view_only)
        break;

      structure = gst_event_get_structure (event);
      event_type = gst_structure_get_string (structure, "event");

      if (strcmp (event_type, "key-press") == 0) {
        key_event = key_press = TRUE;
      } else if (strcmp (event_type, "key-release") == 0) {
        key_event = TRUE;
        key_press = FALSE;
      }

      if (key_event) {
#ifdef HAVE_X11
        const gchar *key;
        KeySym key_sym;

        key = gst_structure_get_string (structure, "key");
        key_sym = XStringToKeysym (key);

        if (key_sym != NoSymbol)
          rfb_decoder_send_key_event (src->decoder, key_sym, key_press);
#endif
        break;
      }

      gst_structure_get_double (structure, "pointer_x", &x);
      gst_structure_get_double (structure, "pointer_y", &y);
      gst_structure_get_int (structure, "button", &button);


      x += src->decoder->offset_x;
      y += src->decoder->offset_y;

      if (strcmp (event_type, "mouse-move") == 0) {
        GST_LOG_OBJECT (src, "sending mouse-move event "
            "button_mask=%d, x=%d, y=%d", src->button_mask, (gint) x, (gint) y);
        rfb_decoder_send_pointer_event (src->decoder, src->button_mask,
            (gint) x, (gint) y);
      } else if (strcmp (event_type, "mouse-button-release") == 0) {
        src->button_mask &= ~(1 << (button - 1));
        GST_LOG_OBJECT (src, "sending mouse-button-release event "
            "button_mask=%d, x=%d, y=%d", src->button_mask, (gint) x, (gint) y);
        rfb_decoder_send_pointer_event (src->decoder, src->button_mask,
            (gint) x, (gint) y);
      } else if (strcmp (event_type, "mouse-button-press") == 0) {
        src->button_mask |= (1 << (button - 1));
        GST_LOG_OBJECT (src, "sending mouse-button-press event "
            "button_mask=%d, x=%d, y=%d", src->button_mask, (gint) x, (gint) y);
        rfb_decoder_send_pointer_event (src->decoder, src->button_mask,
            (gint) x, (gint) y);
      }
      break;
    default:
      break;
  }

  return TRUE;
}
