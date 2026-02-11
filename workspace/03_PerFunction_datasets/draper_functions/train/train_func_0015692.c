grl_operation_get_data (guint operation_id)
{
  OperationData *data = g_hash_table_lookup (operations,
                                             GUINT_TO_POINTER (operation_id));

  if (!data) {
    GRL_WARNING ("Invalid operation %u", operation_id);
    return NULL;
  }

  return data->user_data;
}
