read_code2memory(FILE *fp, size_t x, char *code)
{
	size_t	 charsread = 0;
	char	 linebuf[CODESIZE];
	char	*ch;
	char	*codech;

	rewind(fp);

	while (fgets(linebuf, CODESIZE, fp) != NULL) {
		if ((strncasecmp(linebuf, "code", 4)) == 0) {
			ch = &linebuf[0];
			codech = &code[0];
			while (*ch != '\0') {
				if (isdigit(*ch) != 0) {
					*codech = *ch;
					codech++;
					charsread++;
				}
				ch++;

			}
			if (charsread + 1 <= CODESIZE)
				code[charsread + 1] = '\0';
			else
				code[CODESIZE - 1] = '\0';
			return;
		}
	}
}
