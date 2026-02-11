set_property (GObject      *object,
              guint         prop_id,
              const GValue *value,
              GParamSpec   *pspec)
{
    CutFileStreamReaderPrivate *priv;

    priv = CUT_FILE_STREAM_READER_GET_PRIVATE(object);
    switch (prop_id) {
      case PROP_FILE_NAME:
        free_file_name(priv);
        priv->file_name = g_value_dup_string(value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
