file_cvt(unsigned char *name, unsigned char *fixed)
{
    unsigned char c;
    int size, ext, cnt;

    size = 8;
    ext = 0;
    while (*name) {
	c = *name;
	if (c < ' ' || c > 0x7e || strchr("*?<>|\"/", c)) {
	    printf("Invalid character in name. Use \\ooo for special "
		   "characters.\n");
	    return 0;
	}
	if (c == '.') {
	    if (ext) {
		printf("Duplicate dots in name.\n");
		return 0;
	    }
	    while (size--)
		*fixed++ = ' ';
	    size = 3;
	    ext = 1;
	    name++;
	    continue;
	}
	if (c == '\\') {
	    c = 0;
	    for (cnt = 3; cnt; cnt--) {
		if (*name < '0' || *name > '7') {
		    printf("Invalid octal character.\n");
		    return 0;
		}
		c = c * 8 + *name++ - '0';
	    }
	    if (cnt < 4) {
		printf("Expected three octal digits.\n");
		return 0;
	    }
	    name += 3;
	}
	if (islower(c))
	    c = toupper(c);
	if (size) {
	    *fixed++ = c;
	    size--;
	}
	name++;
    }
    if (*name || size == 8)
	return 0;
    if (!ext) {
	while (size--)
	    *fixed++ = ' ';
	size = 3;
    }
    while (size--)
	*fixed++ = ' ';
    return 1;
}
