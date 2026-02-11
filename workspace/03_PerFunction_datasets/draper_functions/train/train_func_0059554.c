infinoted_autosave_session_save(InfinotedAutosave* autosave,
                                InfinotedAutosaveSession* session)
{
  InfdDirectory* directory;
  InfdDirectoryIter* iter;
  GError* error;
  gchar* path;
  InfBuffer* buffer;

  directory = autosave->directory;
  iter = &session->iter;
  error = NULL;

  if(session->timeout != NULL)
  {
    inf_io_remove_timeout(
      infd_directory_get_io(directory),
      session->timeout
    );

    session->timeout = NULL;
  }

  buffer = inf_session_get_buffer(
    infd_session_proxy_get_session(session->proxy)
  );

  inf_signal_handlers_block_by_func(
    G_OBJECT(buffer),
    G_CALLBACK(infinoted_autosave_buffer_notify_modified_cb),
    session
  );

  if(infd_directory_iter_save_session(directory, iter, &error) == FALSE)
  {
    path = infd_directory_iter_get_path(directory, iter);
    g_warning(
      _("Failed to auto-save session \"%s\": %s\n\n"
        "Will retry in %u seconds."),
      path,
      error->message,
      session->autosave->autosave_interval
    );

    g_free(path);
    g_error_free(error);

    infinoted_autosave_session_start(session->autosave, session);
  }
  else
  {


    inf_buffer_set_modified(INF_BUFFER(buffer), FALSE);
  }

  inf_signal_handlers_unblock_by_func(
    G_OBJECT(buffer),
    G_CALLBACK(infinoted_autosave_buffer_notify_modified_cb),
    session
  );
}
