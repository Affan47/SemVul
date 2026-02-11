knh_throw(CTX ctx, ksfp_t *sfp, long start)
{
	if(IS_Exception(ctx->e)) {
		ksfp_t *sp = (sfp == NULL) ? ctx->esp : sfp + start;
		kExceptionHandler *hdr = ctx->ehdrNC;
		if((ctx->e)->uline == 0) {
			(ctx->e)->uline = knh_stack_uline(ctx, sfp);
		}
		while(ctx->stack <= sp) {
			if(sp[0].mtdNC != NULL && isCalledMethod(ctx, sp)) {
				knh_Exception_addStackTrace(ctx, ctx->e, sp+1);
				sp[0].mtdNC = 0;
			}
			if(sp[0].hdr == hdr) {
				size_t i = 0, size = knh_Array_size(hdr->stacklist);
				for(i = 0; i < size; i++) {
					kObject *o = knh_Array_n(hdr->stacklist, i);
					O_cTBL(o)->cdef->checkout(ctx, RAWPTR(o), 1);
				}
				kArrayrimSize(ctx, hdr->stacklist, 0);
#ifdef K_USING_SETJMP_
				knh_longjmp(DP(hdr)->jmpbuf, 1);
#else
				knh_ExceptionHandler_longjmp(ctx, hdr);
#endif
				goto L_NOCATCH;
			}
			sp--;
		}
		L_NOCATCH:;
		knh_write_Object(ctx, KNH_STDERR, UPCAST(ctx->e), FMT_dump);
		knh_exit(ctx, 0);
	}
}
