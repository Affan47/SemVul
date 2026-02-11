setup_dp(X509 *x, DIST_POINT *dp)
	{
	X509_NAME *iname = NULL;
	int i;
	if (dp->reasons)
		{
		if (dp->reasons->length > 0)
			dp->dp_reasons = dp->reasons->data[0];
		if (dp->reasons->length > 1)
			dp->dp_reasons |= (dp->reasons->data[1] << 8);
		dp->dp_reasons &= CRLDP_ALL_REASONS;
		}
	else
		dp->dp_reasons = CRLDP_ALL_REASONS;
	if (!dp->distpoint || (dp->distpoint->type != 1))
		return;
	for (i = 0; i < sk_GENERAL_NAME_num(dp->CRLissuer); i++)
		{
		GENERAL_NAME *gen = sk_GENERAL_NAME_value(dp->CRLissuer, i);
		if (gen->type == GEN_DIRNAME)
			{
			iname = gen->d.directoryName;
			break;
			}
		}
	if (!iname)
		iname = X509_get_issuer_name(x);

	DIST_POINT_set_dpname(dp->distpoint, iname);

	}
