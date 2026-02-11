free_variable(struct variable * var)
{
	struct variable *var_next;

	if (var == NULL)
		return;
	var_next = var->next;
	ecpg_free(var);

	while (var_next)
	{
		var = var_next;
		var_next = var->next;
		ecpg_free(var);
	}
}
