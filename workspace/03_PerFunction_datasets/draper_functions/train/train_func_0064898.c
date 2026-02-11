expr_name_validate_r1c1 (const char *name)
{
	const char *p = name;
	gint i;

	if (p[0] != 'R' && p[0] != 'r')
		return TRUE;
	p++;

	for (i = 0; p[0] && g_ascii_isdigit (p[0]); p = g_utf8_next_char (p))
		i++;
	if (i==0)
		return TRUE;
	if (p[0] != 'C' && p[0] != 'c')
		return TRUE;
	p++;
	for (i = 0; p[0] && g_ascii_isdigit (p[0]); p = g_utf8_next_char (p))
		i++;
	if (i==0)
		return TRUE;
	return (p[0] != '\0');
}
