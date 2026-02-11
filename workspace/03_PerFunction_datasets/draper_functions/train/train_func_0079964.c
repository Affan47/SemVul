json_serializable_default_deserialize_property (JsonSerializable *serializable,
                                                const gchar      *property_name,
                                                GValue           *value,
                                                GParamSpec       *pspec,
                                                JsonNode         *property_node)
{
  g_return_val_if_fail (JSON_IS_SERIALIZABLE (serializable), FALSE);
  g_return_val_if_fail (property_name != NULL, FALSE);
  g_return_val_if_fail (value != NULL, FALSE);
  g_return_val_if_fail (pspec != NULL, FALSE);
  g_return_val_if_fail (property_node != NULL, FALSE);

  return json_serializable_real_deserialize (serializable,
                                             property_name,
                                             value, pspec,
                                             property_node);
}
