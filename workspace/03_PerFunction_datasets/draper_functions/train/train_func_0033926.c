cfg_cmd(const char *arg)
{
    char *key, *val;
    char *buffer;

    buffer = strdup(arg);
    key = strip(buffer, 0);
    for (val = key; *val; val++) {
	if (*val == '=') {
	    *val++ = '\0';
	    break;
	}
    }
    if (*key == '\0' || *val == '\0') {
	free(buffer);
	return -1;
    }

    if (!validchars(key, 0)) {
	free(buffer);
	return -1;
    }

    cfg_add("", key, val, 1);

    free(buffer);
    return 0;
}
