OutputStream_reftrace(CTX ctx, kRawPtr *o FTRARG)
{
	kOutputStream *w = (kOutputStream*)o;
	KNH_ADDNNREF(ctx, (w->encNULL));
	KNH_ADDNNREF(ctx, (w->bufferNULL));
	KNH_ADDREF(ctx, (w->path));
	KNH_SIZEREF(ctx);
}
