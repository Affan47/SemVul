SetDefaultALVL(struct ChanInfo *cptr)
{
	if (cptr->access_lvl == NULL)
		cptr->access_lvl = MyMalloc(sizeof(int) * CA_SIZE);

	memcpy(cptr->access_lvl, DefaultAccess, sizeof(int) * CA_SIZE);
}
