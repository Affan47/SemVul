rl_free_undo_list ()
{
  UNDO_LIST *release, *orig_list;

  orig_list = rl_undo_list;
  while (rl_undo_list)
    {
      release = rl_undo_list;
      rl_undo_list = rl_undo_list->next;

      if (release->what == UNDO_DELETE)
	xfree (release->text);

      xfree (release);
    }
  rl_undo_list = (UNDO_LIST *)NULL;
  replace_history_data (-1, (histdata_t *)orig_list, (histdata_t *)NULL);
}
