copy_new_to_old()
	{
	interp_list *current, *new_old, *prev_old;


	current = current_interps->next_interp;
	prev_old = old_interps;
	while (current != NULL)
		{
		if ((new_old = (interp_list *) malloc(sizeof(interp_list))) == NULL)
			print_error(MEMORY,"");
		strcpy(new_old->name,current->name);
		new_old->indicator = '\0';
		new_old->next_interp = NULL;
		prev_old->next_interp = new_old;
		prev_old = prev_old->next_interp;
		current = current->next_interp;
		}
	}
