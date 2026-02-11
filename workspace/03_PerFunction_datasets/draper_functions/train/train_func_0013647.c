idl_old_init_private(backend *be,struct attrinfo *a)
{
	idl_private *priv = NULL;

	PR_ASSERT(NULL != a);
	PR_ASSERT(NULL == a->ai_idl);

	priv = (idl_private*) slapi_ch_malloc(sizeof(idl_private));
	if (NULL == priv) {
		return -1;
	}
	{
	    priv->idl_maxids = 0;
	    priv->idl_maxindirect = 0;
	}
#ifdef IDL_LOCKING_ENABLE
	priv->idl_rwlock = slapi_new_rwlock();

	if (NULL == priv->idl_rwlock) {
		slapi_ch_free((void**)&priv);
		return -1;
	}
#endif
	a->ai_idl = (void*)priv;
	return 0;
}
