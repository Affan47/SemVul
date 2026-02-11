list_Get(list *l,long index)
{
	void *r = NULL;
	if(index < l->num)
	{
		r = l->items[index];
	}
	return(r);
}
