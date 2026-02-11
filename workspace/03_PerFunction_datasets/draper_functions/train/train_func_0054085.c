var_is_rel(Var *var)
{
	return (bool)
		!(var_is_inner(var) || var_is_outer(var));
}
