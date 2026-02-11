php_conv_get_uint_prop_ex(const HashTable *ht, unsigned int *pretval, char *field_name, size_t field_name_len)
{
	long l;
	php_conv_err_t err;

	*pretval = 0;

	if ((err = php_conv_get_ulong_prop_ex(ht, &l, field_name, field_name_len)) == PHP_CONV_ERR_SUCCESS) {
		*pretval = l;
	}
	return err;
}
