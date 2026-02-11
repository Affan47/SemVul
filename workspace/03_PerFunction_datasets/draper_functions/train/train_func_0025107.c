lash_get_event(lash_client_t * client_ptr)
{
  ASSERT(client_ptr == &g_client);
  dispatch();

  if (g_busy)
  {
    if (g_event.type == LASH_Restore_Data_Set && list_empty(&g_pending_configs))
    {

      lash_send_event(&g_client, &g_event);
      ASSERT(!g_busy);
    }
    else
    {
      return NULL;
    }
  }

  if (g_event.type == 0)
  {
    if (g_quit)
    {
      g_event.type = LASH_Quit;
    }
    else
    {
      return NULL;
    }
  }

  if (g_event.type == LASH_Save_Data_Set)
  {
    clean_pending_configs();

  }
  else if (g_event.type == LASH_Restore_Data_Set)
  {
    load_configs(g_event.string);

  }
  else if (g_event.type == LASH_Restore_File)
  {

  }
  else if (g_event.type == LASH_Save_File)
  {

  }
  else if (g_event.type == LASH_Quit)
  {

  }

  g_busy = true;
  log_debug("App begins to process event %d (%s)", g_event.type, g_event.string);
  return &g_event;
}
