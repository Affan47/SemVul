rl_maybe_save_line ()
{
  if (_rl_saved_line_for_history == 0)
    {
      _rl_saved_line_for_history = (HIST_ENTRY *)xmalloc (sizeof (HIST_ENTRY));
      _rl_saved_line_for_history->line = savestring (rl_line_buffer);
      _rl_saved_line_for_history->timestamp = (char *)NULL;
      _rl_saved_line_for_history->data = (char *)rl_undo_list;
    }

  return 0;
}
