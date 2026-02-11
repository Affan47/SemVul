FreeExportTbl (export_table_t *tbl)
{
    int		i;
    item_ref_t	*p, *q;

    for (i = 0;  i <  tbl->tableSize;  i++) {
	for (p = tbl->table[i];  p != NIL(item_ref_t *); ) {
	    q = p->next;
	    FREE (p);
	    p = q;
	}
    }

    if (tbl->itemMap != NIL(item_t **))
	FREE (tbl->itemMap);

    FREE (tbl);

}
