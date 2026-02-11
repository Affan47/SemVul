compare_name_id(const name_id_t *n1, const name_id_t *n2)
{
	if(n1->type == name_ord && n2->type == name_ord)
	{
		return n1->name.i_name - n2->name.i_name;
	}
	else if(n1->type == name_str && n2->type == name_str)
	{
		if(n1->name.s_name->type == str_char
		&& n2->name.s_name->type == str_char)
		{
			return strcasecmp(n1->name.s_name->str.cstr, n2->name.s_name->str.cstr);
		}
		else if(n1->name.s_name->type == str_unicode
		&& n2->name.s_name->type == str_unicode)
		{
			return strcmpiW(n1->name.s_name->str.wstr, n2->name.s_name->str.wstr);
		}
		else
		{
			internal_error(__FILE__, __LINE__, "Can't yet compare strings of mixed type\n");
		}
	}
	else if(n1->type == name_ord && n2->type == name_str)
		return 1;
	else if(n1->type == name_str && n2->type == name_ord)
		return -1;
	else
		internal_error(__FILE__, __LINE__, "Comparing name-ids with unknown types (%d, %d)\n",
				n1->type, n2->type);

	return 0;
}
