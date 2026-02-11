gst_index_set_property (GObject * object, guint prop_id,
    const GValue * value, GParamSpec * pspec)
{
  GstIndex *index;

  index = GST_INDEX (object);

  switch (prop_id) {
    case ARG_RESOLVER:
      index->method = (GstIndexResolverMethod) g_value_get_enum (value);
      index->resolver = resolvers[index->method].resolver;
      index->resolver_user_data = resolvers[index->method].user_data;
      break;
    default:
      G_OBJECT_WARN_INVALID_PROPERTY_ID (object, prop_id, pspec);
      break;
  }
}
