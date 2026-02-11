is_date (GnmFuncFlags typ, GOFormat const *explicit)
{
	return (typ == GNM_FUNC_AUTO_DATE ||
		(typ == AF_EXPLICIT && go_format_is_date (explicit)));
}
