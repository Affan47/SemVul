findFuncByOid(Oid oid)
{
	int			i;

	for (i = 0; i < numFuncs; i++)
	{
		if (funinfo[i].dobj.catId.oid == oid)
			return &funinfo[i];
	}
	return NULL;
}
