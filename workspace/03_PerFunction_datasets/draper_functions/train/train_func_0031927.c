free_config (void)
{
    int     i;

    for (i = 0; i < Vars_Size; i++)
	if (Vars[i].type == VAR_TYPE_STR && *(char **) Vars[i].val)
	    FREE (*(char **) Vars[i].val);
	else if (Vars[i].type == VAR_TYPE_LIST)
	    list_free (*(LIST **) Vars[i].val, free_pointer);
}
