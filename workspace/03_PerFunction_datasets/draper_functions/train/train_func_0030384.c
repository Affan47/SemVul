cha_get_type_id(char *x)
{
    int i;

    if (x == NULL) {
	cha_exit_file(1, "null string for type");
	return 0;
    }

    if (x[0] == '*' && x[1] == '\0')
	return 0;

    for (i = 1; strcmp(Cha_type[i].name, x);) {
	if (!Cha_type[++i].name) {
	    cha_exit_file(1, "type `%s' is undefined", x);
	}
    }

    return i;
}
