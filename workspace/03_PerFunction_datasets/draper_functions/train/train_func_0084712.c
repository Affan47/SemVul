TypeName(QCC_type_t *type)
{
	static char buffer[2][512];
	static int op;
	char *ret;


	op++;
	ret = buffer[op&1];
	if (type->type == ev_field)
	{
		type = type->aux_type;
		*ret++ = '.';
	}
	*ret = 0;

	if (type->type == ev_function)
	{
		strcat(ret, type->aux_type->name);
		strcat(ret, " (");
		type = type->param;
		while(type)
		{
			strcat(ret, type->name);
			type = type->next;

			if (type)
				strcat(ret, ", ");
		}
		strcat(ret, ")");
	}
	else if (type->type == ev_entity && type->parentclass)
	{
		ret = buffer[op&1];
		*ret = 0;
		strcat(ret, "class ");
		strcat(ret, type->name);


	}
	else
		strcpy(ret, type->name);

	return buffer[op&1];
}
