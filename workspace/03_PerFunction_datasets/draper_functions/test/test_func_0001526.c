param_to_order (const char *s)
{
    if (s == NULL || *s == '\0') {

	return 0;
    } else if (integer_string(s)) {
	return atoi(s);
    } else if (gretl_is_scalar(s)) {
	return (int) gretl_scalar_get_value(s, NULL);
    } else {
	return -1;
    }
}
