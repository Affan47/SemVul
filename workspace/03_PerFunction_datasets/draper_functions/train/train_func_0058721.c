emit_info_symbol (MonoAotCompile *acfg, const char *name)
{
	char symbol [256];

	if (acfg->llvm) {
		emit_label (acfg, name);

		sprintf (symbol, "%s%s%s", acfg->user_symbol_prefix, acfg->global_prefix, name);
		emit_label (acfg, symbol);
		emit_global_inner (acfg, symbol, FALSE);
	} else {
		emit_label (acfg, name);
	}
}
