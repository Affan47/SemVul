_adcli_str_dupn (void *data,
                 size_t len)
{
	char *result;

	result = malloc (len + 1);
	return_val_if_fail (result, NULL);

	memcpy (result, data, len);
	result[len] = '\0';
	return result;
}
