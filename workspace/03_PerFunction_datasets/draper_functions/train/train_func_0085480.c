list_nth(LIST *list, UINT n)
{
	UINT i;
	LIST *l;

	if(!list) return NULL;


	l = list;
	for(i=0;i<n;i++)
	{
		if(!l) return NULL;
		l = l->next;
	}

	return l;
}
