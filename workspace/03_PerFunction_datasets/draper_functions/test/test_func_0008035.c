ZZ_NewList(void)
{
    ZZList *list = (ZZList *) PORT_ZAlloc (sizeof (ZZList));
    if (list)
	ZZ_InitList (list);
    return list;
}
