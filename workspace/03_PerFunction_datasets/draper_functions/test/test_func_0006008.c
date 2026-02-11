gst_qt_mux_request_new_pad (GstElement * element,
    GstPadTemplate * templ, const gchar * req_name)
{
  GstElementClass *klass = GST_ELEMENT_GET_CLASS (element);
  GstQTMux *qtmux = GST_QT_MUX_CAST (element);
  GstQTPad *collect_pad;
  GstPad *newpad;
  gboolean audio;
  gchar *name;

  if (templ->direction != GST_PAD_SINK)
    goto wrong_direction;

  if (qtmux->state > GST_QT_MUX_STATE_STARTED)
    goto too_late;

  if (templ == gst_element_class_get_pad_template (klass, "audio_%d")) {
    audio = TRUE;
    name = g_strdup_printf ("audio_%02d", qtmux->audio_pads++);
  } else if (templ == gst_element_class_get_pad_template (klass, "video_%d")) {
    audio = FALSE;
    name = g_strdup_printf ("video_%02d", qtmux->video_pads++);
  } else
    goto wrong_template;

  GST_DEBUG_OBJECT (qtmux, "Requested pad: %s", name);


  newpad = gst_pad_new_from_template (templ, name);
  g_free (name);
  collect_pad = (GstQTPad *)
      gst_collect_pads_add_pad_full (qtmux->collect, newpad, sizeof (GstQTPad),
      (GstCollectDataDestroyNotify) (gst_qt_mux_pad_reset));

  gst_qt_mux_pad_reset (collect_pad);
  collect_pad->trak = atom_trak_new (qtmux->context);
  atom_moov_add_trak (qtmux->moov, collect_pad->trak);

  qtmux->sinkpads = g_slist_append (qtmux->sinkpads, collect_pad);


  if (audio)
    gst_pad_set_setcaps_function (newpad,
        GST_DEBUG_FUNCPTR (gst_qt_mux_audio_sink_set_caps));
  else
    gst_pad_set_setcaps_function (newpad,
        GST_DEBUG_FUNCPTR (gst_qt_mux_video_sink_set_caps));


  qtmux->collect_event = (GstPadEventFunction) GST_PAD_EVENTFUNC (newpad);
  gst_pad_set_event_function (newpad,
      GST_DEBUG_FUNCPTR (gst_qt_mux_sink_event));

  gst_pad_set_active (newpad, TRUE);
  gst_element_add_pad (element, newpad);

  return newpad;


wrong_direction:
  {
    GST_WARNING_OBJECT (qtmux, "Request pad that is not a SINK pad.");
    return NULL;
  }
too_late:
  {
    GST_WARNING_OBJECT (qtmux, "Not providing request pad after stream start.");
    return NULL;
  }
wrong_template:
  {
    GST_WARNING_OBJECT (qtmux, "This is not our template!");
    return NULL;
  }
}
