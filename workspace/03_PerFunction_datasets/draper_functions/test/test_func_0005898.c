pdf_debug_indent(char *prefix, int level, char *suffix)
{
	int i;

	printf("%s", prefix);

	for (i = 0; i < level; i++)
		printf("\t");

	printf("%s", suffix);
}
