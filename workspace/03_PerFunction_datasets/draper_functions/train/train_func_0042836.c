latex_print_to_file(char * text, FILE *file)
{
	int i;

	if(text == NULL) return;

	for(i = 0; i < (int)strlen(text); i++)
	{
		if(text[i] == '_' || text[i] == '&' || text[i] == '%' || text[i] == '#') fputs("\\", file);
		fputc(text[i], file);
	}
}
