class_loaded (MonoProfiler *prof, MonoClass *klass, int result)
{
	uint64_t now;
	char *name;
	int nlen;
	MonoImage *image;
	LogBuffer *logbuffer;
	if (result != MONO_PROFILE_OK)
		return;
	if (InterlockedRead (&runtime_inited))
		name = mono_type_get_name (mono_class_get_type (klass));
	else
		name = type_name (klass);
	nlen = strlen (name) + 1;
	image = mono_class_get_image (klass);
	logbuffer = ensure_logbuf (
		EVENT_SIZE  +
		LEB128_SIZE  +
		EVENT_SIZE  +
		LEB128_SIZE  +
		LEB128_SIZE  +
		LEB128_SIZE  +
		nlen
	);
	now = current_time ();
	ENTER_LOG (logbuffer, "class");
	emit_byte (logbuffer, TYPE_END_LOAD | TYPE_METADATA);
	emit_time (logbuffer, now);
	emit_byte (logbuffer, TYPE_CLASS);
	emit_ptr (logbuffer, klass);
	emit_ptr (logbuffer, image);
	emit_value (logbuffer, 0);
	memcpy (logbuffer->data, name, nlen);
	logbuffer->data += nlen;

	if (runtime_inited)
		mono_free (name);
	else
		free (name);
	EXIT_LOG (logbuffer);
	if (logbuffer->next)
		safe_send (prof, logbuffer);
	process_requests (prof);
}
