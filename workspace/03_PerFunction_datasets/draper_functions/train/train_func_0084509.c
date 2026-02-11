egg_sm_client_set_mode (EggSMClientMode mode)
{
  EggSMClientMode old_mode = global_client_mode;

  g_return_if_fail (global_client == NULL || global_client_mode == EGG_SM_CLIENT_MODE_DISABLED);
  g_return_if_fail (!(global_client != NULL && mode == EGG_SM_CLIENT_MODE_DISABLED));

  global_client_mode = mode;

  if (global_client != NULL && old_mode == EGG_SM_CLIENT_MODE_DISABLED)
    {
      if (EGG_SM_CLIENT_GET_CLASS (global_client)->startup)
        EGG_SM_CLIENT_GET_CLASS (global_client)->startup (global_client, sm_client_id);
    }
}
