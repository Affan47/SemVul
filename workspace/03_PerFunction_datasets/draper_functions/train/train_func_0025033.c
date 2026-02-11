der_parse_hex_heim_integer (const char *p, heim_integer *data)
{
    ssize_t len;

    data->length = 0;
    data->negative = 0;
    data->data = NULL;

    if (*p == '-') {
	p++;
	data->negative = 1;
    }

    len = strlen(p);
    if (len <= 0) {
	data->data = NULL;
	data->length = 0;
	return EINVAL;
    }

    data->length = (len / 2) + 1;
    data->data = malloc(data->length);
    if (data->data == NULL) {
	data->length = 0;
	return ENOMEM;
    }

    len = hex_decode(p, data->data, data->length);
    if (len < 0) {
	free(data->data);
	data->data = NULL;
	data->length = 0;
	return EINVAL;
    }

    {
	unsigned char *q = data->data;
	while(len > 0 && *q == 0) {
	    q++;
	    len--;
	}
	data->length = len;
	memmove(data->data, q, len);
    }
    return 0;
}
