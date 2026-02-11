get_lang (char *name)
{
    char    *lang = malloc (strlen (name) + 1);
    char    *l = lang;
    char    c;

    while ((c = *name++))
    {
	if (isupper ((int) (unsigned char) c))
	    c = tolower ((int) (unsigned char) c);
	if (c == '_')
	    c = '-';
	if (c == ' ')
	    continue;
	*l++ = c;
    }
    *l++ = '\0';
    return lang;
}
