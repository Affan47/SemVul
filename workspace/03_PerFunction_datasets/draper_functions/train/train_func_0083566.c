abook_list_append(abook_list **list, char *str)
{
	abook_list *tmp;

	if(!str)
		return;

	for(tmp = *list; tmp && tmp->next; tmp = tmp->next)
		;

	if(tmp) {
		tmp->next = xmalloc(sizeof(abook_list));
		tmp = tmp->next;
	} else
		tmp = *list = xmalloc(sizeof(abook_list));

	tmp->data = xstrdup(str);
	tmp->next = NULL;
}
