AddrTblInsert (addr_tbl_t *tbl, Addr_t addr, void *obj)
{
    int		h = HASH(tbl,addr);
    item_t	*p;

    for (p = tbl->buckets[h];  (p != NIL(item_t *)) && (p->addr != addr);  p = p->next)
	continue;
    if (p == NIL(item_t *)) {
	p		= NEW_OBJ(item_t);
	p->addr		= addr;
	p->obj		= obj;
	p->next		= tbl->buckets[h];
	tbl->buckets[h]	= p;
	tbl->numItems++;
    }
    else if (p->obj != obj)
	Die ("AddrTblInsert: %#x mapped to multiple objects", addr);

}
