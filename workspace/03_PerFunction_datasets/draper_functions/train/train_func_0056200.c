variable_is_retvar(Var_table *var)
{
    if (var->name != NULL && strcmp(var->name, "$retvar") == 0)
	return TRUE;
    else
	return FALSE;
}
