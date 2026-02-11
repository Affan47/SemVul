exp_pseudoroot(struct svc_rqst *rqstp, struct svc_fh *fhp)
{
	struct svc_export *exp;
	__be32 rv;

	exp = rqst_find_fsidzero_export(rqstp);
	if (IS_ERR(exp))
		return nfserrno(PTR_ERR(exp));
	rv = fh_compose(fhp, exp, exp->ex_path.dentry, NULL);
	exp_put(exp);
	return rv;
}
