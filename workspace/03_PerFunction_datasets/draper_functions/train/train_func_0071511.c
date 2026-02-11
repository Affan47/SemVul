print_cap_bitmap(const char *val)
{
#define MASK(x) (1U << (x))
	unsigned long long temp;
	__u32 caps[2];
	int i, found=0;
	char *p, buf[600];

	errno = 0;
	temp = strtoull(val, NULL, 16);
	if (errno) {
		char *out;
                asprintf(&out, "conversion error(%s)", val);
                return out;
	}

        caps[0] = temp & 0xFFFFFFFF;
        caps[1] = (temp & 0xFFFFFFFF) >> 32;
	p = buf;
	for (i=0; i <= CAP_LAST_CAP; i++) {
		if (MASK(i%32) & caps[i/32]) {
			const char *s;
			if (found)
				p = stpcpy(p, ",");
			s = cap_i2s(i);
			if (s != NULL)
				p = stpcpy(p, s);
			found = 1;
		}
	}
	if (found == 0)
		return strdup("none");
	return strdup(buf);
}
