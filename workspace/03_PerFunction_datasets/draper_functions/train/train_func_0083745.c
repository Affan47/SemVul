set_locale()
{
    char *s;

    c_token++;
    if (END_OF_COMMAND) {
	init_locale();
    } else if ((s = try_to_get_string())) {
	set_var_locale(s);
	free(s);
    } else
	int_error(c_token, "expected string");
}
