CNFSofft2hex(off_t offset, bool leadingzeros) {
    static char	buf[24];
    char	*p;

    if (sizeof(off_t) <= sizeof(unsigned long)) {
	snprintf(buf, sizeof(buf), (leadingzeros) ? "%016lx" : "%lx",
                 (unsigned long) offset);
    } else {
	int	i;

	for (i = 0; i < CNFSLASIZ; i++)
	    buf[i] = '0';
	for (i = CNFSLASIZ - 1; i >= 0; i--) {
	    buf[i] = hextbl[offset & 0xf];
	    offset >>= 4;
	}
    }
    if (! leadingzeros) {
	for (p = buf; *p == '0'; p++)
	    ;
	if (*p != '\0')
		return p;
	else
		return p - 1;

    } else
	return buf;
}
