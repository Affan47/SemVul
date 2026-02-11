freevariables(variable ** p_vars)
{
	variable * temp, * head;
	head = *p_vars;


	while(head)
	{
		temp = head->next;


		free(head->type);
		free(head->name);
		free(head->value);
		free(head->typenotarray);
		free(head->file);
		free(head->description);
		free(head);
		head = temp;
	}

	*p_vars = NULL;
}
