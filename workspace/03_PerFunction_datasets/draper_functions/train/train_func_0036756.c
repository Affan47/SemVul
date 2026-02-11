ks_tuple2str(krb5_context context, int n_ks_tuple,
	     krb5_key_salt_tuple *ks_tuple, char ***ks_tuple_strs)
{
	size_t i;
	char **ksnames;
	char *ename, *sname;
	krb5_error_code rc = KRB5_PROG_ETYPE_NOSUPP;

	*ks_tuple_strs = NULL;
	if (n_ks_tuple < 1)
		return 0;

	if ((ksnames = calloc(n_ks_tuple + 1, sizeof (*ksnames))) == NULL)
		return (errno);

	for (i = 0; i < n_ks_tuple; i++) {
	    if (krb5_enctype_to_string(context, ks_tuple[i].ks_enctype, &ename))
		goto out;
	    if (krb5_salttype_to_string(context, ks_tuple[i].ks_enctype,
					ks_tuple[i].ks_salttype, &sname))
		goto out;

	    if (asprintf(&ksnames[i], "%s:%s", ename, sname) == -1) {
		    rc = errno;
		    free(ename);
		    free(sname);
		    goto out;
	    }
	    free(ename);
	    free(sname);
	}

	ksnames[i] = NULL;
	*ks_tuple_strs = ksnames;
	return 0;

out:
	for (i = 0; i < n_ks_tuple; i++)
		free(ksnames[i]);
	free(ksnames);
	return (rc);
}
