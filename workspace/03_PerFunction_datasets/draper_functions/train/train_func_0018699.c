free_datum(DATUM * d)
{
    u_int     i;
    TokenRef *ref;
#if RESUME
    FileList *flist;
#endif

	if(d->numTokens > 0)
	{
		for (i = 0; i < d->numTokens; i++)
		{
			ref = &d->tokens[i];

			ASSERT(validate_flist(ref->flist));


			if(ref->dlist->prev)
				ref->dlist->prev->next = ref->dlist->next;
			else
			{


				ref->flist->list = ref->dlist->next;
			}


			if(ref->dlist->next)
				ref->dlist->next->prev = ref->dlist->prev;

			if(ref->dlist != NULL)
				FREE(ref->dlist);

			ref->flist->count--;

			if(ref->flist->count == 0)
			{
				ASSERT(ref->flist->list == 0);
				hash_remove(global.FileHash, ref->flist->key);
				FREE(ref->flist->key);
				FREE(ref->flist);
			}
		}

		FREE(d->tokens);
	}

#if RESUME
    flist = hash_lookup(global.MD5Hash, d->hash);
    if(flist)
    {
        DList *list;

        ASSERT(validate_flist (flist));
        for (list = flist->list; list; list = list->next)
        {
            if(list->data == d)
            {
                if(list->prev)
                    list->prev->next =  list->next;
                else
                {

                    flist->list = list->next;
                }
                if(list->next)
                    list->next->prev = list->prev;
                FREE(list);
                break;
            }
        }

        flist->count--;

        if(flist->count == 0)
        {
            ASSERT(flist->list == 0);
            hash_remove(global.MD5Hash, flist->key);
            FREE(flist->key);
            FREE(flist);
        }
    }
    else
        log_message_level(LOG_LEVEL_DEBUG, "free_datum: error, no hash entry for file %s", d->filename);
#endif

    BlockHeapFree(d->user->con->uopt->files_heap, d);
}
