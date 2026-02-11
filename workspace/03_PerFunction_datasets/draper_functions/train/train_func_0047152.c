tpl_log_manager_get_dates_async (TplLogManager *manager,
    TpAccount *account,
    TplEntity *target,
    gint type_mask,
    GAsyncReadyCallback callback,
    gpointer user_data)
{
  TplLogManagerEventInfo *event_info = tpl_log_manager_event_info_new ();
  TplLogManagerAsyncData *async_data = tpl_log_manager_async_data_new ();
  GSimpleAsyncResult *simple;

  g_return_if_fail (TPL_IS_LOG_MANAGER (manager));
  g_return_if_fail (TP_IS_ACCOUNT (account));
  g_return_if_fail (TPL_IS_ENTITY (target));

  event_info->account = g_object_ref (account);
  event_info->target = g_object_ref (target);
  event_info->type_mask = type_mask;

  async_data->manager = g_object_ref (manager);
  async_data->request = event_info;
  async_data->request_free =
    (TplLogManagerFreeFunc) tpl_log_manager_event_info_free;
  async_data->cb = callback;
  async_data->user_data = user_data;

  simple = g_simple_async_result_new (G_OBJECT (manager),
      _tpl_log_manager_async_operation_cb, async_data,
      tpl_log_manager_get_dates_async);

  g_simple_async_result_run_in_thread (simple, _get_dates_async_thread, 0,
      NULL);

  g_object_unref (simple);
}
