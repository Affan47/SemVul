strip_illegals (char *s)
{
    int i;

    if (*s == '\0') return;

    for (i=1; s[i]!='\0'; i++) {
	if (!isalnum(s[i])) {
	    s[i] = '_';
	}
    }
}
