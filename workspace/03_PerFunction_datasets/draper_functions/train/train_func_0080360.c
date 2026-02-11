fileNameChecks(char *name)
{
    while (*name != '\0') {
	if (*name == '^' || *name == ' ')
	    *name = '_';
	name++;
    }
}
