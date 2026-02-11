iter_loop (GelCtx *ctx, GelETree *n, gboolean body_first, gboolean is_while)
{
	GelEvalLoop *evl;
	GelETree *l;

	GEL_GET_L(n,l);

	EDEBUG("   ITER LOOP");

	GE_PUSH_STACK (ctx, ctx->current,
		       GE_ADDWHACKARG (GE_POST, ctx->whackarg));
	if (body_first) {
		EDEBUG ("    BODY FIRST");
		evl = evl_new (NULL, gel_copynode (l), is_while, body_first);
		GE_PUSH_STACK (ctx, evl, GE_LOOP_LOOP);
		ctx->current = evl->body;
		ctx->post = FALSE;
		ctx->whackarg = FALSE;
	} else {
		EDEBUG("    CHECK FIRST");
		evl = evl_new (gel_copynode(l), NULL, is_while, body_first);
		GE_PUSH_STACK (ctx, evl, GE_LOOP_COND);
		ctx->current = evl->condition;
		ctx->post = FALSE;
		ctx->whackarg = FALSE;
	}
}
