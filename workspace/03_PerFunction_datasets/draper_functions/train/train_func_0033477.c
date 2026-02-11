cfg_doc_enum(cfg_printer_t *pctx, const cfg_type_t *type) {
	const char * const *p;
	cfg_print_chars(pctx, "( ", 2);
	for (p = type->of; *p != NULL; p++) {
		cfg_print_cstr(pctx, *p);
		if (p[1] != NULL)
			cfg_print_chars(pctx, " | ", 3);
	}
	cfg_print_chars(pctx, " )", 2);
}
