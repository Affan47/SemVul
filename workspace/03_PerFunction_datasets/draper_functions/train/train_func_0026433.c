gst_mixer_class_init (GstMixerClass * klass)
{
#ifndef GST_DISABLE_DEPRECATED
  static gboolean initialized = FALSE;


  if (!initialized) {
    gst_mixer_signals[SIGNAL_RECORD_TOGGLED] =
        g_signal_new ("record-toggled",
        GST_TYPE_MIXER, G_SIGNAL_RUN_LAST,
        G_STRUCT_OFFSET (GstMixerClass, record_toggled),
        NULL, NULL,
        gst_interfaces_marshal_VOID__OBJECT_BOOLEAN, G_TYPE_NONE, 2,
        GST_TYPE_MIXER_TRACK, G_TYPE_BOOLEAN);
    gst_mixer_signals[SIGNAL_MUTE_TOGGLED] =
        g_signal_new ("mute-toggled",
        GST_TYPE_MIXER, G_SIGNAL_RUN_LAST,
        G_STRUCT_OFFSET (GstMixerClass, mute_toggled),
        NULL, NULL,
        gst_interfaces_marshal_VOID__OBJECT_BOOLEAN, G_TYPE_NONE, 2,
        GST_TYPE_MIXER_TRACK, G_TYPE_BOOLEAN);
    gst_mixer_signals[SIGNAL_VOLUME_CHANGED] =
        g_signal_new ("volume-changed",
        GST_TYPE_MIXER, G_SIGNAL_RUN_LAST,
        G_STRUCT_OFFSET (GstMixerClass, volume_changed),
        NULL, NULL,
        gst_interfaces_marshal_VOID__OBJECT_POINTER, G_TYPE_NONE, 2,
        GST_TYPE_MIXER_TRACK, G_TYPE_POINTER);
    gst_mixer_signals[SIGNAL_OPTION_CHANGED] =
        g_signal_new ("option-changed",
        GST_TYPE_MIXER, G_SIGNAL_RUN_LAST,
        G_STRUCT_OFFSET (GstMixerClass, option_changed),
        NULL, NULL,
        gst_interfaces_marshal_VOID__OBJECT_STRING, G_TYPE_NONE, 2,
        GST_TYPE_MIXER_OPTIONS, G_TYPE_STRING);

    initialized = TRUE;
  }
#endif

  klass->mixer_type = GST_MIXER_SOFTWARE;


  klass->list_tracks = NULL;
  klass->set_volume = NULL;
  klass->get_volume = NULL;
  klass->set_mute = NULL;
  klass->set_record = NULL;
  klass->set_option = NULL;
  klass->get_option = NULL;
}
