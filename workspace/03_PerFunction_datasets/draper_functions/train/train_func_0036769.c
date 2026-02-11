lmo_close(lmo_archive_t *ar)
{
	lmo_entry_t *head  = NULL;
	lmo_entry_t *entry = NULL;

	if( ar != NULL )
	{
		entry = ar->index;

		while( entry != NULL )
		{
			head = entry->next;
			free(entry);
			entry = head;
		}

		head = entry = NULL;

		if( (ar->mmap != NULL) && (ar->mmap != MAP_FAILED) )
			munmap(ar->mmap, ar->length);

		close(ar->fd);
		free(ar);

		ar = NULL;
	}
}
