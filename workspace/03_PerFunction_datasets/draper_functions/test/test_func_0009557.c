lh_retrieve(_LHASH *lh, const void *data)
	{
	unsigned long hash;
	LHASH_NODE **rn;
	void *ret;

	lh->error=0;
	rn=getrn(lh,data,&hash);

	if (*rn == NULL)
		{
		lh->num_retrieve_miss++;
		return(NULL);
		}
	else
		{
		ret= (*rn)->data;
		lh->num_retrieve++;
		}
	return(ret);
	}
