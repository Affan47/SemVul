tp_base_client_add_approver_filter (TpBaseClient *self,
    GHashTable *filter)
{
  g_return_if_fail (filter != NULL);
  tp_base_client_take_approver_filter (self,
      _tp_base_client_copy_filter (filter));
}
