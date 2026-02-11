verify_f(hx509_context hxcontext, void *ctx, hx509_cert c)
{
    struct verify *v = ctx;
    int ret;

    ret = hx509_verify_path(hxcontext, v->ctx, c, v->chain);
    if (ret) {
	char *s = hx509_get_error_string(hxcontext, ret);
	printf("verify_path: %s: %d\n", s, ret);
	hx509_free_error_string(s);
	v->errors++;
    } else {
	v->count++;
	printf("path ok\n");
    }

    if (v->hostname) {
	ret = hx509_verify_hostname(hxcontext, c, 0, HX509_HN_HOSTNAME,
				    v->hostname, NULL, 0);
	if (ret) {
	    printf("verify_hostname: %d\n", ret);
	    v->errors++;
	}
    }

    return 0;
}
