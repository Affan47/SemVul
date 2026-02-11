get_property (GObject    *object,
              guint       prop_id,
              GValue     *value,
              GParamSpec *pspec)
{
    CutXMLStream *stream = CUT_XML_STREAM(object);

    switch (prop_id) {
      case PROP_RUN_CONTEXT:
        g_value_set_object(value, G_OBJECT(stream->run_context));
        break;
      case PROP_STREAM_FUNCTION:
        g_value_set_pointer(value, stream->stream_function);
        break;
      case PROP_STREAM_FUNCTION_USER_DATA:
        g_value_set_pointer(value, stream->stream_function_user_data);
        break;
      case PROP_STREAM_FUNCTION_USER_DATA_DESTROY_FUNCTION:
        g_value_set_pointer(value, stream->stream_function_user_data_destroy_function);
        break;
      default:
        G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
        break;
    }
}
