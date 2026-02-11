G_tolcase(char *string)
{
    char *p;

    for (p = string; *p; p++) {

	if (*p >= 'A' && *p <= 'Z')
	    *p -= 'A' - 'a';
    }

    return (string);
}
