execute_builtin_or_function (words, builtin, var, redirects,
			     fds_to_close, flags)
     WORD_LIST *words;
     sh_builtin_func_t *builtin;
     SHELL_VAR *var;
     REDIRECT *redirects;
     struct fd_bitmap *fds_to_close;
     int flags;
{
  int result;
  REDIRECT *saved_undo_list;
  sh_builtin_func_t *saved_this_shell_builtin;

  if (do_redirections (redirects, RX_ACTIVE|RX_UNDOABLE) != 0)
    {
      cleanup_redirects (redirection_undo_list);
      redirection_undo_list = (REDIRECT *)NULL;
      dispose_exec_redirects ();
      return (EX_REDIRFAIL);
    }

  saved_this_shell_builtin = this_shell_builtin;
  saved_undo_list = redirection_undo_list;


  if (builtin == exec_builtin)
    {
      dispose_redirects (saved_undo_list);
      saved_undo_list = exec_redirection_undo_list;
      exec_redirection_undo_list = (REDIRECT *)NULL;
    }
  else
    dispose_exec_redirects ();

  if (saved_undo_list)
    {
      begin_unwind_frame ("saved redirects");
      add_unwind_protect (cleanup_redirects, (char *)saved_undo_list);
    }

  redirection_undo_list = (REDIRECT *)NULL;

  if (builtin)
    result = execute_builtin (builtin, words, flags, 0);
  else
    result = execute_function (var, words, flags, fds_to_close, 0, 0);


  fflush (stdout);
  fpurge (stdout);
  if (ferror (stdout))
    clearerr (stdout);


  if (builtin == command_builtin && this_shell_builtin == exec_builtin)
    {
      if (saved_undo_list)
	dispose_redirects (saved_undo_list);
      redirection_undo_list = exec_redirection_undo_list;
      saved_undo_list = exec_redirection_undo_list = (REDIRECT *)NULL;
      discard_unwind_frame ("saved_redirects");
    }

  if (saved_undo_list)
    {
      redirection_undo_list = saved_undo_list;
      discard_unwind_frame ("saved redirects");
    }

  if (redirection_undo_list)
    {
      cleanup_redirects (redirection_undo_list);
      redirection_undo_list = (REDIRECT *)NULL;
    }

  return (result);
}
