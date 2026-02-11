free_datum (DATUM * d)
{
    int i;
    TokenRef *ref;

    for (i = 0; i < d->numTokens; i++)
    {
	ref = &d->tokens[i];

	ASSERT (validate_flist (ref->flist));


	if (ref->dlist->prev)
	    ref->dlist->prev->next = ref->dlist->next;
	else
	{


	    ref->flist->list = ref->dlist->next;
	}


	if (ref->dlist->next)
	    ref->dlist->next->prev = ref->dlist->prev;

	FREE (ref->dlist);

	ref->flist->count--;

	if (ref->flist->count == 0)
	{
	    ASSERT (ref->flist->list == 0);
	    hash_remove (File_Table, ref->flist->key);
	    FREE (ref->flist->key);
	    FREE (ref->flist);
	}
    }

    FREE (d->tokens);


#if RESUME
    flist = hash_lookup (MD5, d->hash);
    if (flist)
    {
	ASSERT (validate_flist (flist));
	flist->list = list_delete (flist->list, d);
	flist->count--;

	if (flist->count == 0)
	{
	    ASSERT (flist->list == 0);
	    hash_remove (MD5, flist->key);
	    FREE (flist->key);
	    FREE (flist);
	}
    }
    else
	log_message ("free_datum: error, no hash entry for file %s", d->filename);
    FREE (d->hash);
#endif

    FREE (d->filename);
    FREE (d);
}
