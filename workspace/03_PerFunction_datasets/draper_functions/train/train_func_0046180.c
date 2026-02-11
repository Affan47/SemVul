matchfunc(krb5_context context, void *ptr, const krb5_creds *creds)
{
    struct ctx *ctx = ptr;
    if (krb5_compare_creds(context, ctx->whichfields, &ctx->mcreds, creds))
	return TRUE;
    return FALSE;
}
