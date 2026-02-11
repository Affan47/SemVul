grl_operation_options_get_skip (GrlOperationOptions *options)
{
  const GValue *value  =
      g_hash_table_lookup (options->priv->data, GRL_OPERATION_OPTION_SKIP);

  if (value)
    return g_value_get_uint (value);

  return SKIP_DEFAULT;
}
