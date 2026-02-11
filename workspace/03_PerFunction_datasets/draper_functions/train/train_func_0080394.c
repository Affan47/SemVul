rl_free_undo_list ()
{
  while (rl_undo_list)
    {
      UNDO_LIST *release = rl_undo_list;
      rl_undo_list = rl_undo_list->next;

      if (release->what == UNDO_DELETE)
	free (release->text);

      free (release);
    }
  rl_undo_list = (UNDO_LIST *)NULL;
}
