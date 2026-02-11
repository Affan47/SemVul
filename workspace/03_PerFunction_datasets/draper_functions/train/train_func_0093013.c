clear(unsigned char val)
    {
        register struct cellule *cur = first;

        while(cur != NULL)
        {
	    (void)memset(cur->data, val, cur->size);
            cur = cur->next;
        }
    }
