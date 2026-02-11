v2i_idp(const X509V3_EXT_METHOD *method, X509V3_CTX *ctx,
		     STACK_OF(CONF_VALUE) *nval)
	{
	ISSUING_DIST_POINT *idp = NULL;
	CONF_VALUE *cnf;
	char *name, *val;
	int i, ret;
	idp = ISSUING_DIST_POINT_new();
	if (!idp)
		goto merr;
	for(i = 0; i < sk_CONF_VALUE_num(nval); i++)
		{
		cnf = sk_CONF_VALUE_value(nval, i);
		name = cnf->name;
		val = cnf->value;
		ret = set_dist_point_name(&idp->distpoint, ctx, cnf);
		if (ret > 0)
			continue;
		if (ret < 0)
			goto err;
		if (!strcmp(name, "onlyuser"))
			{
			if (!X509V3_get_value_bool(cnf, &idp->onlyuser))
				goto err;
			}
		else if (!strcmp(name, "onlyCA"))
			{
			if (!X509V3_get_value_bool(cnf, &idp->onlyCA))
				goto err;
			}
		else if (!strcmp(name, "onlyAA"))
			{
			if (!X509V3_get_value_bool(cnf, &idp->onlyattr))
				goto err;
			}
		else if (!strcmp(name, "indirectCRL"))
			{
			if (!X509V3_get_value_bool(cnf, &idp->indirectCRL))
				goto err;
			}
		else if (!strcmp(name, "onlysomereasons"))
			{
			if (!set_reasons(&idp->onlysomereasons, val))
				goto err;
			}
		else
			{
                        X509V3err(X509V3_F_V2I_IDP, X509V3_R_INVALID_NAME);
                        X509V3_conf_err(cnf);
                        goto err;
			}
		}
	return idp;

	merr:
	X509V3err(X509V3_F_V2I_IDP,ERR_R_MALLOC_FAILURE);
	err:
	ISSUING_DIST_POINT_free(idp);
	return NULL;
	}
