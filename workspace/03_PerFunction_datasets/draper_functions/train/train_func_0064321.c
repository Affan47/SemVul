b_vformat_construct (b_VFormat *evc, const char *str)
{
	g_return_if_fail (str != NULL);

	if (*str)
		_parse (evc, str);
}
