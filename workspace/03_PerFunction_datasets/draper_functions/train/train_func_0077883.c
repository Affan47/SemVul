print_prot(const char *val, unsigned int is_mmap)
{
	unsigned int prot, i;
	int cnt = 0, limit;
	char buf[144];
	char *out;

	errno = 0;
        prot = strtoul(val, NULL, 16);
	if (errno) {
		if (asprintf(&out, "conversion error(%s)", val) < 0)
			out = NULL;
		return out;
	}
	buf[0] = 0;
        if ((prot & 0x07) == 0) {

                strcat(buf, "PROT_NONE");
		return strdup(buf);
        }
	if (is_mmap)
		limit = 4;
	else
		limit = 3;
        for (i=0; i<limit; i++) {
                if (prot_table[i].value & prot) {
                        if (!cnt) {
                                strcat(buf,
				prot_strings + prot_table[i].offset);
                                cnt++;
                        } else {
                                strcat(buf, "|");
                                strcat(buf,
				prot_strings + prot_table[i].offset);
			}
                }
        }
	if (buf[0] == 0)
		snprintf(buf, sizeof(buf), "0x%s", val);
	return strdup(buf);
}
