server_thread_func (gpointer user_data)
{
  Server *server = user_data;

  server->thread_context = g_main_context_new ();
  server->thread_loop = g_main_loop_new (server->thread_context, FALSE);

  g_main_context_push_thread_default (server->thread_context);

  if (!server_export_object (server, &server->thread_initialization_error))
    {
      server->thread_initialized = TRUE;
      goto out;
    }

  server->thread_initialized = TRUE;

  g_main_loop_run (server->thread_loop);

 out:
  g_main_context_pop_thread_default (server->thread_context);
  return NULL;
}
