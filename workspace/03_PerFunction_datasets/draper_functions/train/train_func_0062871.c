history_add(char * newCommand)
{
	hnode * newnode = (hnode *) malloc (sizeof(hnode));

	newnode->command_text = (char *) calloc ((strlen(newCommand) +1) * sizeof(char), 1);
	strncpy(newnode->command_text, newCommand, strlen(newCommand));
	newnode->command_text[strlen(newnode->command_text)] = '\0';


	if(history_size == HISTORYMAX)
	{
		hnode * tofree = tail->next;
		tail->next = tofree->next;

		if(tofree->command_text)
			free (tofree->command_text);
		free (tofree);
	}

	if(history_size < HISTORYMAX)
		++history_size;

	if(!tail)
	{
		tail = newnode;
		tail->next = tail;
	}
	else
	{
		newnode->next = tail->next;
		tail->next = newnode;
		tail = newnode;
	}
}
