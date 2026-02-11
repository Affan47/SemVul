_braille_console_setup(char **str, char **brl_options)
{
	if (!strncmp(*str, "brl,", 4)) {
		*brl_options = "";
		*str += 4;
	} else if (!strncmp(*str, "brl=", 4)) {
		*brl_options = *str + 4;
		*str = strchr(*brl_options, ',');
		if (!*str)
			pr_err("need port name after brl=\n");
		else
			*((*str)++) = 0;
	} else
		return NULL;

	return *str;
}
