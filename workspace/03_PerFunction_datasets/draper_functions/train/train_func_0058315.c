expand_one_file(FILE *f, const char *cell)
{
    static char buf[1024];
    char *p;

    while (fgets (buf, sizeof(buf), f) != NULL) {
	if(buf[0] == '>') {
	    for(p = buf; *p && !isspace((unsigned char)*p) && *p != '#'; p++)
		;
	    *p = '\0';
	    if(strncmp(buf + 1, cell, strlen(cell)) == 0)
		return buf + 1;
	}
	buf[0] = '\0';
    }
    return NULL;
}
