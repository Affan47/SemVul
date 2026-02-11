applix_parse_sheet (ApplixReadState *state, unsigned char **buffer,
		    char const separator)
{
	Sheet *sheet;


	char *tmp = strchr (*buffer, separator);

	if (tmp == NULL) {
		applix_parse_error (state, "Invalid sheet name.");
		return NULL;
	}

	*tmp = '\0';
	sheet = applix_fetch_sheet (state, *buffer);
	*buffer = tmp+1;
	return sheet;
}
