hx509_verify_init_ctx(hx509_context context, hx509_verify_ctx *ctx)
{
    hx509_verify_ctx c;

    c = calloc(1, sizeof(*c));
    if (c == NULL)
	return ENOMEM;

    c->max_depth = HX509_VERIFY_MAX_DEPTH;

    *ctx = c;

    return 0;
}
