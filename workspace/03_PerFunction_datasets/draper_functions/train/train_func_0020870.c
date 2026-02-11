add_single_dir (struct dir_entry *entry, int verbose)
{
  struct dir_entry *ptr, *prev;

  ptr = dir_entries;
  prev = ptr;
  while (ptr != NULL)
    {

      if (ptr->ino == entry->ino && ptr->dev == entry->dev)
	{
	  if (opt_verbose && verbose)
	    error (0, 0, _("Path `%s' given more than once"), entry->path);

	  ptr->flag = entry->flag;
	  free (entry->path);
	  free (entry);
	  break;
	}
      prev = ptr;
      ptr = ptr->next;
    }

  if (ptr == NULL && dir_entries == NULL)
    dir_entries = entry;
  else if (ptr == NULL)
    prev->next = entry;
}
