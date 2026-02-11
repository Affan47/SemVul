repl_objset_new(FNFree destructor)
{
	Repl_Objset *p;

	p = (Repl_Objset *)slapi_ch_malloc(sizeof(Repl_Objset));
	p->lock = PR_NewLock();
	if (NULL == p->lock)
	{
		slapi_ch_free((void **)&p);
	}
	p->objects = llistNew();
	p->destructor = destructor;
	return p;
}
