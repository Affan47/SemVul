cfg_remove_properties(
		const CFG_CONTEXT con,
		enum cfg_property_type type,
		char *str, ...)
{
	va_list ap;
	enum cfg_property_type tmp_type;
	char * tmp_str;
	int ret = 1;


	tmp_type = type;
	tmp_str  = str;
	va_start(ap, str);


	while (tmp_type != CFG_EOT && tmp_str != NULL) {
		ret &= cfg_remove_property(con, tmp_type, tmp_str);
		if (!ret)
			break;
		tmp_type = va_arg(ap, enum cfg_property_type);
		if (tmp_type == CFG_EOT)
			break;
		tmp_str  = va_arg(ap, char *);
	}


	va_end(ap);

	return ret;
}
