sk_delete(_STACK *st, int loc)
	{
	char *ret;
	int i,j;

	if(!st || (loc < 0) || (loc >= st->num)) return NULL;

	ret=st->data[loc];
	if (loc != st->num-1)
		{
		j=st->num-1;
		for (i=loc; i<j; i++)
			st->data[i]=st->data[i+1];


		}
	st->num--;
	return(ret);
	}
