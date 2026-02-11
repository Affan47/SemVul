insert_breakpoint (MonoSeqPointInfo *seq_points, MonoDomain *domain, MonoJitInfo *ji, MonoBreakpoint *bp, MonoError *error)
{
	int i, count;
	BreakpointInstance *inst;
	SeqPoint *sp = NULL;

	if (error)
		mono_error_init (error);

	for (i = 0; i < seq_points->len; ++i) {
		sp = &seq_points->seq_points [i];

		if (sp->il_offset == bp->il_offset)
			break;
	}

	if (i == seq_points->len) {


		for (i = 0; i < seq_points->len; ++i) {
			sp = &seq_points->seq_points [i];

			if (sp->il_offset != METHOD_ENTRY_IL_OFFSET && sp->il_offset != METHOD_EXIT_IL_OFFSET && sp->il_offset + 1 == bp->il_offset)
				break;
		}
	}

	if (i == seq_points->len) {
		char *s = g_strdup_printf ("Unable to insert breakpoint at %s:%d, seq_points=%d\n", mono_method_full_name (jinfo_get_method (ji), TRUE), bp->il_offset, seq_points->len);

		for (i = 0; i < seq_points->len; ++i)
			DEBUG (1, fprintf (log_file, "%d\n", seq_points->seq_points [i].il_offset));

		if (error) {
			mono_error_set_error (error, MONO_ERROR_GENERIC, "%s", s);
			g_warning ("%s", s);
			g_free (s);
			return;
		} else {
			g_warning ("%s", s);
			g_free (s);
			return;
		}
	}

	inst = g_new0 (BreakpointInstance, 1);
	inst->sp = sp;
	inst->native_offset = sp->native_offset;
	inst->ip = (guint8*)ji->code_start + sp->native_offset;
	inst->ji = ji;
	inst->domain = domain;

	mono_loader_lock ();

	g_ptr_array_add (bp->children, inst);

	count = GPOINTER_TO_INT (g_hash_table_lookup (bp_locs, inst->ip));
	g_hash_table_insert (bp_locs, inst->ip, GINT_TO_POINTER (count + 1));
	mono_loader_unlock ();

	if (sp->native_offset == SEQ_POINT_NATIVE_OFFSET_DEAD_CODE) {
		DEBUG (1, fprintf (log_file, "[dbg] Attempting to insert seq point at dead IL offset %d, ignoring.\n", (int)bp->il_offset));
	} else if (count == 0) {
#ifdef MONO_ARCH_SOFT_DEBUG_SUPPORTED
		mono_arch_set_breakpoint (ji, inst->ip);
#else
		NOT_IMPLEMENTED;
#endif
	}

	DEBUG(1, fprintf (log_file, "[dbg] Inserted breakpoint at %s:0x%x.\n", mono_method_full_name (jinfo_get_method (ji), TRUE), (int)sp->il_offset));
}
