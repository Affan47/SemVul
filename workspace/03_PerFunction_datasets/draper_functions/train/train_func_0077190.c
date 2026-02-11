ret_string(krb5_storage *sp, int ucs2, size_t len, char **s)
{
    krb5_error_code ret;
    uint16_t *data = NULL;

    *s = malloc(len + 1);
    if (*s == NULL)
	return ENOMEM;
    CHECK_SIZE(krb5_storage_read(sp, *s, len), len);

    (*s)[len] = '\0';

    if (ucs2) {
	unsigned int flags = WIND_RW_LE;
	size_t utf16len = len / 2;
	size_t utf8len;

	data = malloc(utf16len * sizeof(data[0]));
	if (data == NULL) {
	    free(*s); *s = NULL;
	    ret = ENOMEM;
	    goto out;
	}

	ret = wind_ucs2read(*s, len, &flags, data, &utf16len);
	free(*s); *s = NULL;
	if (ret) {
	    goto out;
	}

	CHECK(wind_ucs2utf8_length(data, utf16len, &utf8len), 0);

	utf8len += 1;

	*s = malloc(utf8len);
	if (s == NULL) {
	    ret = ENOMEM;
	    goto out;
	}

	CHECK(wind_ucs2utf8(data, utf16len, *s, &utf8len), 0);
    }
    ret = 0;
 out:
    if (data)
	free(data);

    return ret;
}
