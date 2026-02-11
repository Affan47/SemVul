display8_init(char *cset)
{
    	int i;

	for (i = 0; d8[i].cset; i++) {
	    	if (!strcasecmp(cset, d8[i].cset)) {
			return i;
		}
	}
	if (!strcasecmp(cset, "iso10646-1"))
		return ISO10646_IX;
	return -1;
}
