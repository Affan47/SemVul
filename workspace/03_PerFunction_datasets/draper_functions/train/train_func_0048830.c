insert_new(interp_list *current)
	{
	interp_list *new;

	if ((new = (interp_list *) malloc(sizeof(interp_list))) == NULL)
		print_error(MEMORY,"");
	new->next_interp = current->next_interp;
	current->next_interp = new;
	return current;
	}
