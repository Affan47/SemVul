ppdb_primary(ppdb db, jid id)
{
	ppdb cur, top;

	if (db == NULL || id == NULL)
		return NULL;

	cur = _ppdb_get(db, id);

	if (cur == NULL)
		return NULL;


	if (id->user == NULL || id->resource != NULL)
		return cur->x;

	top = cur;
	for (cur = cur->user; cur != NULL; cur = cur->user)
		if (cur->pri >= top->pri)
			top = cur;

	if (top != NULL && top->pri >= 0)
		return top->x;

	return NULL;
}
