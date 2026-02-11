mono_debug_lookup_source_location (MonoMethod *method, guint32 address, MonoDomain *domain)
{
	MonoDebugMethodInfo *minfo;
	MonoDebugSourceLocation *location;
	gint32 offset;

	if (mono_debug_format == MONO_DEBUG_FORMAT_NONE)
		return NULL;

	mono_debugger_lock ();
	minfo = mono_debug_lookup_method_internal (method);
	if (!minfo || !minfo->handle) {
		mono_debugger_unlock ();
		return NULL;
	}

	if (!minfo->handle->ppdb && (!minfo->handle->symfile || !mono_debug_symfile_is_loaded (minfo->handle->symfile))) {
		mono_debugger_unlock ();
		return NULL;
	}

	offset = il_offset_from_address (method, domain, address);
	if (offset < 0) {
		mono_debugger_unlock ();
		return NULL;
	}

	if (minfo->handle->ppdb)
		location = mono_ppdb_lookup_location (minfo, offset);
	else
		location = mono_debug_symfile_lookup_location (minfo, offset);
	mono_debugger_unlock ();
	return location;
}
