php_pack(zval **val, int size, int *map, char *output)
{
	int i;
	char *v;

	convert_to_long_ex(val);
	v = (char *) &Z_LVAL_PP(val);

	for (i = 0; i < size; i++) {
		*output++ = v[map[i]];
	}
}
