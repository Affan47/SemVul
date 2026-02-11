insert_breakpoint (MonoSeqPointInfo *seq_points, MonoDomain *domain, MonoJitInfo *ji, MonoBreakpoint *bp, MonoError *error)
{
	int count;
	BreakpointInstance *inst;
	SeqPointIterator it;
	gboolean it_has_sp = FALSE;

	if (error)
		mono_error_init (error);

	mono_seq_point_iterator_init (&it, seq_points);
	while (mono_seq_point_iterator_next (&it)) {
		if (it.seq_point.il_offset == bp->il_offset) {
			it_has_sp = TRUE;
			break;
		}
	}

	if (!it_has_sp) {


		mono_seq_point_iterator_init (&it, seq_points);
		while (mono_seq_point_iterator_next (&it)) {
			if (it.seq_point.il_offset != METHOD_ENTRY_IL_OFFSET &&
				it.seq_point.il_offset != METHOD_EXIT_IL_OFFSET &&
				it.seq_point.il_offset + 1 == bp->il_offset) {
				it_has_sp = TRUE;
				break;
			}
		}
	}

	if (!it_has_sp) {
		char *s = g_strdup_printf ("Unable to insert breakpoint at %s:%d", mono_method_full_name (jinfo_get_method (ji), TRUE), bp->il_offset);

		mono_seq_point_iterator_init (&it, seq_points);
		while (mono_seq_point_iterator_next (&it))
			DEBUG_PRINTF (1, "%d\n", it.seq_point.il_offset);

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
	inst->il_offset = it.seq_point.il_offset;
	inst->native_offset = it.seq_point.native_offset;
	inst->ip = (guint8*)ji->code_start + it.seq_point.native_offset;
	inst->ji = ji;
	inst->domain = domain;

	mono_loader_lock ();

	g_ptr_array_add (bp->children, inst);

	mono_loader_unlock ();

	dbg_lock ();
	count = GPOINTER_TO_INT (g_hash_table_lookup (bp_locs, inst->ip));
	g_hash_table_insert (bp_locs, inst->ip, GINT_TO_POINTER (count + 1));
	dbg_unlock ();

	if (it.seq_point.native_offset == SEQ_POINT_NATIVE_OFFSET_DEAD_CODE) {
		DEBUG_PRINTF (1, "[dbg] Attempting to insert seq point at dead IL offset %d, ignoring.\n", (int)bp->il_offset);
	} else if (count == 0) {
#ifdef MONO_ARCH_SOFT_DEBUG_SUPPORTED
		mono_arch_set_breakpoint (ji, inst->ip);
#else
		NOT_IMPLEMENTED;
#endif
	}

	DEBUG_PRINTF (1, "[dbg] Inserted breakpoint at %s:[il=0x%x,native=0x%x] [%p](%d).\n", mono_method_full_name (jinfo_get_method (ji), TRUE), (int)it.seq_point.il_offset, (int)it.seq_point.native_offset, inst->ip, count);
}
