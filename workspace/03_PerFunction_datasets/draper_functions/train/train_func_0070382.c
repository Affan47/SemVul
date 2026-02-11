print_updatepolicy(cfg_printer_t *pctx, const cfg_obj_t *obj) {
	if (cfg_obj_isstring(obj))
		cfg_print_ustring(pctx, obj);
	else
		cfg_print_bracketed_list(pctx, obj);
}
