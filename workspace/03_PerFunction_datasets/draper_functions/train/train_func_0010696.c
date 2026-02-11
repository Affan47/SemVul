irc_ircoldcolstr_to_ekgcolstr_nf(session_t *sess, char *str, int strip)
{
	int		col, oldstrip = strip;
	char		mirc_sux_so_much[16] =	"WkbgrypRYGcCBPKw";
	char		mirc_sux_even_more[16] = "xlehszqszhddeqlx";
	string_t	s;

	if (!str || !(*str))
		return xstrdup("");

	s = string_init("");
	if (strip)
		strip = session_int_get(sess, "STRIPMIRCCOL");

	for (;*str;)
	{
		if (*str == 3)
		{

			col = irc_getircoldcol(str+1);
			if (strip)
				goto coloring_finito;
			if (!col) {
				string_append(s, "%n");
				goto coloring_finito;
			}
			if (col&0x20000) {
				string_append_c(s, '%');
				string_append_c(s, mirc_sux_so_much
						[(col>>8)&0xf]);
			}
			if (col&0x10000) {
				string_append_c(s, '%');
				string_append_c(s, mirc_sux_even_more
						[col&0xf]);
			}
coloring_finito:
			str+=(col>>24)&0xff;
		} else if (*str == 2)
			string_append(s, "%T");
		else if (*str == 15)
			string_append(s, "%n");
		else if (*str == 18 || *str == 22)
			string_append(s, "%V");
		else if (*str == 31)
			string_append(s, "%U");
		else if (*str == '%')
			string_append(s, "\\%");
		else if (*str == '\\')
			string_append(s, "\\\\");
		else if ((*str == '/') && (str[1] == '|'))
			string_append(s, "//");
		else
			string_append_c(s, *str);
		str++;
	}
	if (oldstrip)
		string_append(s, "%n");
	return string_free(s, 0);
}
