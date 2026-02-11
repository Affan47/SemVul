_verify_callback_c(void *handle, const void *str_arg)
{
	char *str;
	__DB_STD(ostream) *out;

	str = (char *)str_arg;
	out = (__DB_STD(ostream) *)handle;

	(*out) << str;
	if (out->fail())
		return (EIO);

	return (0);
}
