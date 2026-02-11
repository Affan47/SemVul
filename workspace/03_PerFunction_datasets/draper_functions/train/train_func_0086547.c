mboxname_hash(char *buf, size_t buf_len,
		   const char *root,
		   const char *name)
{
    const char *idx;
    char c, *p;

    snprintf(buf, buf_len, "%s", root);
    buf_len -= strlen(buf);
    buf += strlen(buf);

    if (config_virtdomains && (p = strchr(name, '!'))) {
	*p = '\0';
	if (config_hashimapspool) {
	    c = (char) dir_hash_c(name, config_fulldirhash);
	    snprintf(buf, buf_len, "%s%c/%s", FNAME_DOMAINDIR, c, name);
	}
	else {
	    snprintf(buf, buf_len, "%s%s", FNAME_DOMAINDIR, name);
	}
	*p++ = '!';
	name = p;
	buf_len -= strlen(buf);
	buf += strlen(buf);
    }

    if (config_hashimapspool) {
	idx = strchr(name, '.');
	if (idx == NULL) {
	    idx = name;
	} else {
	    idx++;
	}
	c = (char) dir_hash_c(idx, config_fulldirhash);

	snprintf(buf, buf_len, "/%c/%s", c, name);
    } else {

	snprintf(buf, buf_len, "/%s", name);
    }


    for (p = buf; *p; p++) {
	if (*p == '.') *p = '/';
    }
}
