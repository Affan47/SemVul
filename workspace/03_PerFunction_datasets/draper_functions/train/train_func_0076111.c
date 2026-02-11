crl_sign(struct crl_sign_options *opt, int argc, char **argv)
{
    hx509_crl crl;
    heim_octet_string os;
    hx509_cert signer = NULL;
    hx509_lock lock;
    int ret;

    hx509_lock_init(context, &lock);
    lock_strings(lock, &opt->pass_strings);

    ret = hx509_crl_alloc(context, &crl);
    if (ret)
	errx(1, "crl alloc");

    if (opt->signer_string == NULL)
	errx(1, "signer missing");

    {
	hx509_certs certs = NULL;
	hx509_query *q;

	ret = hx509_certs_init(context, opt->signer_string, 0,
			       NULL, &certs);
	if (ret)
	    hx509_err(context, 1, ret,
		      "hx509_certs_init: %s", opt->signer_string);

	ret = hx509_query_alloc(context, &q);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_query_alloc: %d", ret);

	hx509_query_match_option(q, HX509_QUERY_OPTION_PRIVATE_KEY);

	ret = hx509_certs_find(context, certs, q, &signer);
	hx509_query_free(context, q);
	hx509_certs_free(&certs);
	if (ret)
	    hx509_err(context, 1, ret, "no signer certificate found");
    }

    if (opt->lifetime_string) {
	int delta;

	delta = parse_time(opt->lifetime_string, "day");
	if (delta < 0)
	    errx(1, "Invalid lifetime: %s", opt->lifetime_string);

	hx509_crl_lifetime(context, crl, delta);
    }

    {
	hx509_certs revoked = NULL;
	int i;

	ret = hx509_certs_init(context, "MEMORY:revoked-certs", 0,
			       NULL, &revoked);
	if (ret)
	    hx509_err(context, 1, ret,
		      "hx509_certs_init: MEMORY cert");

	for (i = 0; i < argc; i++) {
	    ret = hx509_certs_append(context, revoked, lock, argv[i]);
	    if (ret)
		hx509_err(context, 1, ret, "hx509_certs_append: %s", argv[i]);
	}

	hx509_crl_add_revoked_certs(context, crl, revoked);
	hx509_certs_free(&revoked);
    }

    hx509_crl_sign(context, signer, crl, &os);

    if (opt->crl_file_string)
	rk_dumpdata(opt->crl_file_string, os.data, os.length);

    free(os.data);

    hx509_crl_free(context, &crl);
    hx509_cert_free(signer);
    hx509_lock_free(lock);

    return 0;
}
