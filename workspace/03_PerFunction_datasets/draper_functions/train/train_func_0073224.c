mono_xdebug_init (const char *options)
{
	MonoImageWriter *w;
	char **args, **ptr;

	args = g_strsplit (options, ",", -1);
	for (ptr = args; ptr && *ptr; ptr ++) {
		char *arg = *ptr;

		if (!strcmp (arg, "gdb"))
			use_gdb_interface = TRUE;
		if (!strcmp (arg, "save-symfiles"))
			save_symfiles = TRUE;
	}


	il_file = fopen ("xdb.il", "w");
	if (il_file == NULL) {
		use_gdb_interface = FALSE;
		g_warning ("** Unable to create xdb.il. Managed symbol names won't be available.");
		return;
	}

	if (use_gdb_interface)
		return;

	unlink ("xdb.s");
	xdebug_fp = fopen ("xdb.s", "w");

	w = img_writer_create (xdebug_fp, FALSE);

	img_writer_emit_start (w);

	xdebug_writer = mono_dwarf_writer_create (w, il_file, 0, TRUE, TRUE);


	img_writer_emit_section_change (w, ".text", 0);
	img_writer_emit_string (w, "");

	mono_dwarf_writer_emit_base_info (xdebug_writer, "JITted code", mono_unwind_get_cie_program ());
}
