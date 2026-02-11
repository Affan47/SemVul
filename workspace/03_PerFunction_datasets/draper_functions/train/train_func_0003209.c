set_property (GObject      *object,
              guint         prop_id,
              const GValue *value,
              GParamSpec   *pspec)
{
    CutXMLStream *stream = CUT_XML_STREAM(object);

    switch (prop_id) {
      case PROP_RUN_CONTEXT:
        attach_to_run_context(CUT_LISTENER(stream),
                              CUT_RUN_CONTEXT(g_value_get_object(value)));
        break;
      case PROP_STREAM_FUNCTION:
        stream->stream_function = g_value_get_pointer(value);
        break;
      case PROP_STREAM_FUNCTION_USER_DATA:
        stream->stream_function_user_data = g_value_get_pointer(value);
        break;
      case PROP_STREAM_FUNCTION_USER_DATA_DESTROY_FUNCTION:
        stream->stream_function_user_data_destroy_function =
            g_value_get_pointer(value);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
