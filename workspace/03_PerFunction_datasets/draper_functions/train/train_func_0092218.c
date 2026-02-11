get_group_name(arg, name_end)
    char_u	*arg;
    char_u	**name_end;
{
    char_u	*rest;

    *name_end = skiptowhite(arg);
    rest = skipwhite(*name_end);


    if (ends_excmd(*arg) || *rest == NUL)
	return NULL;
    return rest;
}
