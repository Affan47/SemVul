get_braced_number(
	GScanner *scanner, gboolean  first, gboolean  last, gfloat *value)
{
	if (first) {
		g_scanner_get_next_token(scanner);
		if (scanner->token != '{') {
			return FALSE;
		}
	}
	g_scanner_get_next_token(scanner);
	if (scanner->token != G_TOKEN_INT) {
		return FALSE;
	}
	*value = (float)scanner->value.v_int/COLOR_SCALING;
	g_scanner_get_next_token(scanner);
	if (last) {
		if (scanner->token != '}') {
			return FALSE;
		}
	} else {
		if (scanner->token != ',') {
			return FALSE;
		}
	}
	return TRUE;
}
