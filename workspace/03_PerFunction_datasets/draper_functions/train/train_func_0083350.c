unity_webapps_indicator_model_get_indicator_property (UnityWebappsIndicatorModel *model,
						      const gchar *indicator_name,
						      const gchar *property_name)
{
  UnityWebappsIndicatorModelIndicator *indicator;
  UnityWebappsIndicatorModelIndicatorValue *indicator_value;
  GQueue *value_queue;

  g_return_val_if_fail (UNITY_WEBAPPS_IS_INDICATOR_MODEL (model), NULL);

  indicator = g_hash_table_lookup (model->priv->indicators_by_name, indicator_name);

  if (indicator == NULL)
    {
      return NULL;
    }

  value_queue = g_hash_table_lookup (indicator->properties_by_name, property_name);

  if (value_queue == NULL)
    return NULL;

  indicator_value = g_queue_peek_tail (value_queue);

  if (indicator_value == NULL)
    return NULL;


  return g_variant_ref (indicator_value->value);
}
