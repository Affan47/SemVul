check_identifier (GISourceScanner *scanner,
		  const char  *s)
{


	if (gi_source_scanner_is_typedef (scanner, s)) {
		return TYPEDEF_NAME;
	} else if (strcmp (s, "__builtin_va_list") == 0) {
		return TYPEDEF_NAME;
	}

	return IDENTIFIER;
}
