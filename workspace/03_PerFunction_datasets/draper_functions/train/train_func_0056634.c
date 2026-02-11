_dbus_babysitter_new (void)
{
  DBusBabysitter *sitter;

  sitter = dbus_new0 (DBusBabysitter, 1);
  if (sitter == NULL)
    return NULL;

  sitter->refcount = 1;

  sitter->socket_to_babysitter = -1;
  sitter->error_pipe_from_child = -1;

  sitter->sitter_pid = -1;
  sitter->grandchild_pid = -1;

  sitter->watches = _dbus_watch_list_new ();
  if (sitter->watches == NULL)
    goto failed;

  return sitter;

 failed:
  _dbus_babysitter_unref (sitter);
  return NULL;
}
