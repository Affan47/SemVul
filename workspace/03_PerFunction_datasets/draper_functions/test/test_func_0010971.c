print_sstring(cfg_printer_t *pctx, const cfg_obj_t *obj) {
	cfg_print_chars(pctx, "\"", 1);
	if ((pctx->flags & CFG_PRINTER_XKEY) != 0) {
		unsigned int len = obj->value.string.length;
		while (len-- > 0)
			cfg_print_chars(pctx, "?", 1);
	} else
		cfg_print_ustring(pctx, obj);
	cfg_print_chars(pctx, "\"", 1);
}
