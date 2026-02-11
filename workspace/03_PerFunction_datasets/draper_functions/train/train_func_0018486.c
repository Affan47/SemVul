fgets_ipc(
    char *dest,
    int len)
{
#ifdef USE_MOUSE
    if (term && term->waitforinput) {

	int c;
	size_t i=0;

	dest[0] = '\0';
	for (i=0; i < len-1; i++) {
	    c = term->waitforinput();
	    if ('\n' == c) {
		dest[i] = '\n';
		i++;
		break;
	    } else if (EOF == c) {
		dest[i] = '\0';
		return (char*) 0;
	    } else {
		dest[i] = c;
	    }
	}
	dest[i] = '\0';
	return dest;
    } else
#endif
	return fgets(dest, len, stdin);
}
