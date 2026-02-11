totem_pl_parser_line_is_empty (const char *line)
{
	guint i;

	if (line == NULL)
		return TRUE;

	for (i = 0; line[i] != '\0'; i++) {
		if (line[i] != '\t' && line[i] != ' ')
			return FALSE;
	}
	return TRUE;
}
