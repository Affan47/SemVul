do_exchange(interp_list *current)
	{
	char temp[NAME_LENGTH];
	boolean found = FALSE;
	interp_list *next_exchange, *pointer;
	next_exchange = 0;

	pointer = current->next_interp;
	current->indicator = '*';


	while (pointer != NULL)
		{
		if (pointer->indicator == 'x')
			{


			if (found) pointer->indicator = '*';
			else
				{
				next_exchange = pointer;
				found = TRUE;
				pointer->indicator = '*';
				}
			}
		pointer = pointer->next_interp;
		}


	if (found)
		{
		strcpy(temp,current->name);
		strcpy(current->name,next_exchange->name);
		strcpy(next_exchange->name,temp);
		}

	return current;
	}
