free_ioput(xmachine_ioput ** p_ioput)
{
	xmachine_ioput * temp, * head;
	head = *p_ioput;

	while(head)
	{
		temp = head->next;
		free(head->filter_function);
		free_rule_data(&head->filter_rule);
		free(head->messagetype);
		free(head->sort_function);
		free(head->sort_key);
		free(head->sort_order);
		free(head);
		head = temp;
	}

	*p_ioput = NULL;
}
