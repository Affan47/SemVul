inf_adopted_algorithm_get_property(GObject* object,
                                   guint prop_id,
                                   GValue* value,
                                   GParamSpec* pspec)
{
  InfAdoptedAlgorithm* log;
  InfAdoptedAlgorithmPrivate* priv;

  log = INF_ADOPTED_ALGORITHM(object);
  priv = INF_ADOPTED_ALGORITHM_PRIVATE(log);

  switch(prop_id)
  {
  case PROP_USER_TABLE:
    g_value_set_object(value, G_OBJECT(priv->user_table));
    break;
  case PROP_BUFFER:
    g_value_set_object(value, G_OBJECT(priv->buffer));
    break;
  case PROP_MAX_TOTAL_LOG_SIZE:
    g_value_set_uint(value, priv->max_total_log_size);
    break;
  case PROP_CURRENT_STATE:
    g_value_set_boxed(value, priv->current);
    break;
  case PROP_BUFFER_MODIFIED_STATE:
    g_value_set_boxed(value, priv->buffer_modified_time);
    break;
  default:
    G_OBJECT_WARN_INVALID_PROPERTY_ID(object, prop_id, pspec);
    break;
  }
}
