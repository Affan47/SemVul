lex_getc(void)
{
    int	c;

    for (;;)
    {
	file_ty         *old;

	c = fgetc(file->fp);
	if (c != EOF)
	    break;
	if (ferror(file->fp))
	    nfatal("%s", file->file_name);
	if (!file->next)
	    break;
	old = file;
	file = old->next;
	fclose(old->fp);
	free(old->file_name);
	free(old);
    }
    if (c == '\n')
	file->line_number++;
    return c;
}
