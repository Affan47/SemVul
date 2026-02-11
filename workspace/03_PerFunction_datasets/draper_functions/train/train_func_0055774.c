antlr3ListRemove	    (pANTLR3_LIST list, ANTLR3_INTKEY key)
{
    pANTLR3_HASH_ENTRY	    entry;

    entry = list->table->removeI(list->table, key);

    if	(entry != NULL)
    {
        return  entry->data;
    }
    else
    {
	return	NULL;
    }
}
