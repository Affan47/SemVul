maybe_get_R_function (const char *s)
{
    if (strlen(s) >= 3 && !strncmp(s, "R.", 2)) {
	return get_R_function_by_name(s + 2);
    } else {
	return 0;
    }
}
