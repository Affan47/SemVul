sgen_check_mod_union_consistency (void)
{
	missing_remsets = FALSE;

	major_collector.iterate_objects (ITERATE_OBJECTS_ALL, (IterateObjectCallbackFunc)check_mod_union_callback, (void*)FALSE);

	sgen_los_iterate_objects ((IterateObjectCallbackFunc)check_mod_union_callback, (void*)TRUE);

	if (!binary_protocol_is_enabled ())
		g_assert (!missing_remsets);
}
