aclmembers(const Acl *acl, Oid **roleids)
{
	Oid		   *list;
	const AclItem *acldat;
	int			i,
				j,
				k;

	if (acl == NULL || ACL_NUM(acl) == 0)
	{
		*roleids = NULL;
		return 0;
	}

	check_acl(acl);


	list = palloc(ACL_NUM(acl) * 2 * sizeof(Oid));
	acldat = ACL_DAT(acl);


	j = 0;
	for (i = 0; i < ACL_NUM(acl); i++)
	{
		const AclItem *ai = &acldat[i];

		if (ai->ai_grantee != ACL_ID_PUBLIC)
			list[j++] = ai->ai_grantee;

		if (ai->ai_grantor != ACL_ID_PUBLIC)
			list[j++] = ai->ai_grantor;
	}


	qsort(list, j, sizeof(Oid), oidComparator);


	k = 0;
	for (i = 1; i < j; i++)
	{
		if (list[k] != list[i])
			list[++k] = list[i];
	}


	*roleids = list;

	return k + 1;
}
