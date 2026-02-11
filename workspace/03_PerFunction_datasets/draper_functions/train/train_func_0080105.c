gst_vader_class_init(GstVaderClass * klass)
{
    GObjectClass *gobject_class;
    GstElementClass *gstelement_class;

    gobject_class = (GObjectClass *) klass;
    gstelement_class = (GstElementClass *) klass;

    gobject_class->set_property = gst_vader_set_property;
    gobject_class->get_property = gst_vader_get_property;
    gobject_class->finalize = gst_vader_finalize;

    g_object_class_install_property
        (G_OBJECT_CLASS(klass), PROP_THRESHOLD,
         g_param_spec_double("threshold", "Threshold",
                             "Volume threshold for speech/silence decision. "
                             "Maximum value corresponds to maximum possible volume. "
                             "Everything with volume below this threshold will be counted as silence",
                             0.0, 1.0, 256.0/32768.0, G_PARAM_READWRITE));
    g_object_class_install_property
        (G_OBJECT_CLASS(klass), PROP_AUTO_THRESHOLD,
         g_param_spec_boolean("auto-threshold", "Automatic Threshold",
                             "Set speech/silence threshold automatically",
                             FALSE, G_PARAM_READWRITE));
    g_object_class_install_property
        (G_OBJECT_CLASS(klass), PROP_RUN_LENGTH,
         g_param_spec_uint64("run-length", "Run length",
                             "Length of drop below threshold before cut_stop (in nanoseconds)",
                             0, G_MAXUINT64, (guint64)(0.5 * GST_SECOND), G_PARAM_READWRITE));
    g_object_class_install_property
        (G_OBJECT_CLASS(klass), PROP_PRE_LENGTH,
         g_param_spec_uint64("pre-length", "Pre-recording buffer length",
                             "Length of pre-recording buffer (in nanoseconds)",
                             0, G_MAXUINT64, (guint64)(0.5 * GST_SECOND), G_PARAM_READWRITE));
    g_object_class_install_property
        (G_OBJECT_CLASS(klass), PROP_SILENT,
         g_param_spec_boolean("silent", "Silent",
                             "Whether the VADER is currently in a silence region",
                              TRUE, G_PARAM_READWRITE));
    g_object_class_install_property
        (gobject_class, PROP_DUMPDIR,
         g_param_spec_string("dump-dir", "Audio dump directory",
                             "Directory in which to write audio segments for debugging",
                             NULL,
                             G_PARAM_READWRITE));

    gst_vader_signals[SIGNAL_VADER_START] =
        g_signal_new("vader_start",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     G_STRUCT_OFFSET(GstVaderClass, vader_start),
                     NULL, NULL,
                     gst_marshal_VOID__INT64,
                     G_TYPE_NONE,
                     1, G_TYPE_UINT64
            );

    gst_vader_signals[SIGNAL_VADER_STOP] =
        g_signal_new("vader_stop",
                     G_TYPE_FROM_CLASS(klass),
                     G_SIGNAL_RUN_LAST,
                     G_STRUCT_OFFSET(GstVaderClass, vader_stop),
                     NULL, NULL,
                     gst_marshal_VOID__INT64,
                     G_TYPE_NONE,
                     1, G_TYPE_UINT64
            );

    GST_DEBUG_CATEGORY_INIT(vader_debug, "vader", 0, "Voice Activity Detection");
}
