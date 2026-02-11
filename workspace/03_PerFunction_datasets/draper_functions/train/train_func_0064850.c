add_sync_pointer(sync_pointer ** p_sync_pointers, sync * current_sync)
{
	sync_pointer * current;


	if((current = (sync_pointer *)malloc(sizeof(sync_pointer))) == NULL)
	{
		printf("Error: Cannot allocate memory\n");
		exit(0);
	}

	current->current_sync = current_sync;
	current->next = *p_sync_pointers;
	*p_sync_pointers = current;
}
