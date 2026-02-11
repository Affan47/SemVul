userdiff_config(const char *k, const char *v)
{
	struct userdiff_driver *drv;

	if ((drv = parse_driver(k, v, "funcname")))
		return parse_funcname(&drv->funcname, k, v, 0);
	if ((drv = parse_driver(k, v, "xfuncname")))
		return parse_funcname(&drv->funcname, k, v, REG_EXTENDED);
	if ((drv = parse_driver(k, v, "binary")))
		return parse_tristate(&drv->binary, k, v);
	if ((drv = parse_driver(k, v, "command")))
		return parse_string(&drv->external, k, v);
	if ((drv = parse_driver(k, v, "textconv")))
		return parse_string(&drv->textconv, k, v);
	if ((drv = parse_driver(k, v, "cachetextconv")))
		return parse_bool(&drv->textconv_want_cache, k, v);
	if ((drv = parse_driver(k, v, "wordregex")))
		return parse_string(&drv->word_regex, k, v);

	return 0;
}
