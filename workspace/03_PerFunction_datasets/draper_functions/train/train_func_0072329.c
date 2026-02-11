konoha_close(konoha_t konoha)
{
	CTX ctx = (kcontext_t*)konoha;
	check_allThreadExit(ctx);
	if(ctx->share->threadCounter > 1) {
		KNH_NTRACE2(ctx, "konoha:close", K_FAILED,
				KNH_LDATA(LOG_msg("stil threads running"),
					LOG_i("threads", ctx->share->threadCounter)));
		return;
	}
#ifdef K_USING_RCGC
	knh_context_reftrace(ctx, (kcontext_t*)ctx, FTRDATA);
#endif
	knh_flush(ctx, KNH_STDOUT);
	{
		KNH_NTRACE2(ctx, "stat:konoha:gc", K_NOTICE,
				KNH_LDATA(LOG_u("gc_count", ctx->stat->gcCount),
				LOG_u("marking_time:ms", ctx->stat->markingTime),
				LOG_u("sweeping_time:ms", ctx->stat->sweepingTime),
				LOG_u("gc_time:ms", ctx->stat->gcTime)));
	}
	((kcontext_t*)ctx)->bufa = NULL;
	knh_Context_free(ctx, (kcontext_t*)ctx);
}
