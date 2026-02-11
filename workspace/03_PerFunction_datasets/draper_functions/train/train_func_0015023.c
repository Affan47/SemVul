request_create(struct request_create_options *opt, int argc, char **argv)
{
    heim_octet_string request;
    hx509_request req;
    int ret, i;
    hx509_private_key signer;
    SubjectPublicKeyInfo key;
    const char *outfile = argv[0];

    memset(&key, 0, sizeof(key));

    get_key(opt->key_string,
	    opt->generate_key_string,
	    opt->key_bits_integer,
	    &signer);

    hx509_request_init(context, &req);

    if (opt->subject_string) {
	hx509_name name = NULL;

	ret = hx509_parse_name(context, opt->subject_string, &name);
	if (ret)
	    errx(1, "hx509_parse_name: %d\n", ret);
	hx509_request_set_name(context, req, name);

	if (opt->verbose_flag) {
	    char *s;
	    hx509_name_to_string(name, &s);
	    printf("%s\n", s);
	}
	hx509_name_free(&name);
    }

    for (i = 0; i < opt->email_strings.num_strings; i++) {
	ret = _hx509_request_add_email(context, req,
				       opt->email_strings.strings[i]);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_request_add_email");
    }

    for (i = 0; i < opt->dnsname_strings.num_strings; i++) {
	ret = _hx509_request_add_dns_name(context, req,
					  opt->dnsname_strings.strings[i]);
	if (ret)
	    hx509_err(context, 1, ret, "hx509_request_add_dns_name");
    }


    ret = hx509_private_key2SPKI(context, signer, &key);
    if (ret)
	errx(1, "hx509_private_key2SPKI: %d\n", ret);

    ret = hx509_request_set_SubjectPublicKeyInfo(context,
						  req,
						  &key);
    free_SubjectPublicKeyInfo(&key);
    if (ret)
	hx509_err(context, 1, ret, "hx509_request_set_SubjectPublicKeyInfo");

    ret = _hx509_request_to_pkcs10(context,
				   req,
				   signer,
				   &request);
    if (ret)
	hx509_err(context, 1, ret, "_hx509_request_to_pkcs10");

    hx509_private_key_free(&signer);
    hx509_request_free(&req);

    if (ret == 0)
	rk_dumpdata(outfile, request.data, request.length);
    der_free_octet_string(&request);

    return 0;
}
