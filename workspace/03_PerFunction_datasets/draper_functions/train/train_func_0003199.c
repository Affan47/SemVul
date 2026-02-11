metadata_file_write(gchar *path, const GList *keywords, const gchar *comment)
{
	SecureSaveInfo *ssi;

	ssi = secure_open(path);
	if (!ssi) return FALSE;

	secure_fprintf(ssi, "#%s comment (%s)\n\n", GQ_APPNAME, VERSION);

	secure_fprintf(ssi, "[keywords]\n");
	while (keywords && secsave_errno == SS_ERR_NONE)
		{
		const gchar *word = keywords->data;
		keywords = keywords->next;

		secure_fprintf(ssi, "%s\n", word);
		}
	secure_fputc(ssi, '\n');

	secure_fprintf(ssi, "[comment]\n");
	secure_fprintf(ssi, "%s\n", (comment) ? comment : "");

	secure_fprintf(ssi, "#end\n");

	return (secure_close(ssi) == 0);
}
