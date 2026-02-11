csnplGetMinCSN (CSNPL *csnpl, PRBool *committed)
{
	csnpldata *data;
	CSN *csn = NULL;
	slapi_rwlock_rdlock (csnpl->csnLock);
	if ((data = (csnpldata*)llistGetHead (csnpl->csnList)) != NULL)
	{
		csn = csn_dup(data->csn);
		if (NULL != committed)
		{
			*committed = data->committed;
		}
	}
	slapi_rwlock_unlock (csnpl->csnLock);

	return csn;
}
