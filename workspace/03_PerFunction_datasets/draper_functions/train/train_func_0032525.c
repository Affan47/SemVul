emit_global (MonoAotCompile *acfg, const char *name, gboolean func)
{
	if (acfg->aot_opts.no_dlsym) {
		g_ptr_array_add (acfg->globals, g_strdup (name));
		img_writer_emit_local_symbol (acfg->w, name, NULL, func);
	} else {
		img_writer_emit_global (acfg->w, name, func);
	}
}
