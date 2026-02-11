AddrToCSymbol (ml_val_t addr)
{
    item_t	*q;


    for (q = AddrTable[ADDRHASH_INDEX(addr, TableSize)];
	 q != NIL(item_t *);
	 q = q->nextAddr)
    {
	if (q->addr == addr)
	   return q->name;
    }

    return NIL(const char *);

}
