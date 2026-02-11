gfarm_auth_method_parse(char *name, enum gfarm_auth_method *methodp)
{
	int i;

	for (i = 0; i < GFARM_ARRAY_LENGTH(gfarm_auth_method_name_value_table);
	     i++) {
		if (strcmp(name, gfarm_auth_method_name_value_table[i].name)
		    == 0) {
			*methodp =
			    gfarm_auth_method_name_value_table[i].method;
			return (GFARM_ERR_NO_ERROR);
		}
	}
	return (GFARM_ERR_NO_SUCH_OBJECT);
}
