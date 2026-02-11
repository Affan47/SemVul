log_line(TEXT_DEST_REC *dest, const char *text)
{
	char **lines, **tmp;

	if (dest->level == MSGLEVEL_NEVER)
		return;


	autolog_open_check(dest);

	if (logs == NULL)
		return;


	lines = g_strsplit(text, "\n", -1);
	for (tmp = lines; *tmp != NULL; tmp++)
		log_single_line(dest->window, dest->server_tag,
				dest->target, dest->level, *tmp);
	g_strfreev(lines);
}
