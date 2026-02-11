AddHashReferences(HashTable h, ListHead *invTable,
		  SegList *listElements, int base, int nv)
{
    Hash hash;
    int  n = base;

    if (! DXInitGetNextHashElement(h))
	goto error;

    while (NULL != (hash = (Hash)DXGetNextHashElement(h)))
    {
	int i;

	for (i = 0; i < nv; i++)
	{
	    int index = hash->v[i];
	    if (invTable[index].invalid)
	    {
		ListElement le = DXNewSegListItem(listElements);
		if (! le)
		    goto error;

		le->index = n;
		le->next  = invTable[index].head;
		invTable[index].head = le;
	    }
	}

	n++;
    }

    return OK;

error:

    return ERROR;
}
