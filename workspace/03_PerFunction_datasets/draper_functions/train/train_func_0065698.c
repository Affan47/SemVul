readline_internal_teardown (eof)
     int eof;
{
  char *temp;
  HIST_ENTRY *entry;


  entry = current_history ();

  if (entry && rl_undo_list)
    {
      temp = savestring (the_line);
      rl_revert_line (1, 0);
      entry = replace_history_entry (where_history (), the_line, (histdata_t)NULL);
      _rl_free_history_entry (entry);

      strcpy (the_line, temp);
      free (temp);
    }


  if (rl_undo_list)
    rl_free_undo_list ();


  _rl_set_insert_mode (RL_IM_INSERT, 0);

  return (eof ? (char *)NULL : savestring (the_line));
}
