ckyCardContext_release(CKYCardContext *ctx)
{
    unsigned long rv = ctx->scard->SCardReleaseContext(ctx->context);
    ctx->context = 0;
    if (rv != SCARD_S_SUCCESS) {
	ctx->lastError = rv;
	return CKYSCARDERR;
    }
    return CKYSUCCESS;
}
