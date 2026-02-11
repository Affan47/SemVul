ves_icall_System_Diagnostics_FileVersionInfo_GetVersionInfo_internal (MonoObject *this, MonoString *filename)
{
	MONO_ARCH_SAVE_REGS;

	STASH_SYS_ASS (this);

	process_get_fileversion (this, mono_string_chars (filename));
	process_set_field_string (this, "filename",
				  mono_string_chars (filename),
				  mono_string_length (filename));
}
