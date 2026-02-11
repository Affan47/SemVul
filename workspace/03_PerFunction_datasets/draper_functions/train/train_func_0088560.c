print_gid(const char *val, unsigned int base)
{
        int gid;
        char name[64];

        errno = 0;
        gid = strtoul(val, NULL, base);
        if (errno) {
		char *out;
		if (asprintf(&out, "conversion error(%s)", val) < 0)
			out = NULL;
                return out;
        }

        return strdup(aulookup_gid(gid, name, sizeof(name)));
}
