continuation_mark_frame (MonoContinuation *cont)
{
	MonoJitTlsData *jit_tls;
	MonoLMF *lmf;
	MonoContext ctx, new_ctx;
	MonoJitInfo *ji, rji;
	int endloop = FALSE;

	if (cont->domain)
		return mono_get_exception_argument ("cont", "Already marked");

	jit_tls = (MonoJitTlsData *)mono_native_tls_get_value (mono_jit_tls_id);
	lmf = mono_get_lmf();
	cont->domain = mono_domain_get ();
	cont->thread_id = mono_native_thread_id_get ();


	memset (&rji, 0, sizeof (rji));
	do {
		ji = mono_find_jit_info (cont->domain, jit_tls, &rji, NULL, &ctx, &new_ctx, NULL, &lmf, NULL, NULL);
		if (!ji || ji == (gpointer)-1) {
			return mono_get_exception_not_supported ("Invalid stack frame");
		}
		ctx = new_ctx;
		if (endloop)
			break;
		if (!ji->is_trampoline && strcmp (jinfo_get_method (ji)->name, "Mark") == 0)
			endloop = TRUE;
	} while (1);

	cont->top_sp = MONO_CONTEXT_GET_SP (&ctx);


	return NULL;
}
