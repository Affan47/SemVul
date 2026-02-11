sdump(const char *in, size_t len)
{
    size_t outlen = 0, i;
    char *out, *oi;

    for (i = 0; i < len; i++) {
	outlen += isprint((unsigned char)in[i]) ? 1 : 4;
    }

    oi = out = (char *)xmalloc(outlen + 1);
    for (i = 0; i < len; i++) {
	if (isprint((unsigned char)in[i])) {
	    *(oi++) = in[i];
	} else {
	    oi += sprintf(oi, "\\x%02X", (unsigned char)in[i]);
	}
    }
    *oi = '\0';
    return out;
}
