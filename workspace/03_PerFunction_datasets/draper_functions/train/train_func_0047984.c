iter_continue_break_op(GelCtx *ctx, gboolean cont)
{
	EDEBUG("  CONTINUE/BREAK");
	for(;;) {
		int flag;
		gpointer data;
		GE_POP_STACK(ctx,data,flag);
		EDEBUG("   POPPED STACK");
		switch(flag & GE_MASK) {
		case GE_EMPTY_STACK:
			EDEBUG("    EMPTY");
			goto iter_continue_break_done;
		case GE_FUNCCALL:
			EDEBUG("    FOUND FUNCCCALL MAKE IT NULL THEN");
			gel_errorout (_("Continue or break outside a loop, "
					"assuming \"return null\""));
			gel_freetree(data);

			d_popcontext ();


			GE_POP_STACK(ctx,data,flag);

			g_assert ((flag & GE_MASK) == GE_POST);
			if (flag & GE_WHACKARG) {

				gel_freetree (data);
			} else {
				freetree_full(data,TRUE,FALSE);
				((GelETree *)data)->type = GEL_NULL_NODE;
			}

			iter_pop_stack(ctx);
			return;
		case GE_LOOP_LOOP:
			LOOP_BREAK_CONT (GelEvalLoop, evl_free_with_cond, GE_LOOP_LOOP);
		case GE_FOR:
			LOOP_BREAK_CONT (GelEvalFor, evf_free, GE_FOR);
		case GE_FORIN:
			LOOP_BREAK_CONT (GelEvalForIn, evfi_free, GE_FORIN);
		default:
			ev_free_special_data(ctx,data,flag);
			break;
		}
	}
iter_continue_break_done:
	EDEBUG("   GOT TO TOP OF THE STACK, SO JUST JUMP OUT OF GLOBAL CONTEXT");
	gel_errorout (_("Continue or break outside a loop, "
			"assuming \"return null\""));

	ctx->current = NULL;
	ctx->post = FALSE;
	ctx->whackarg = FALSE;
	freetree_full(ctx->res,TRUE,FALSE);
	ctx->res->type = GEL_NULL_NODE;
}
