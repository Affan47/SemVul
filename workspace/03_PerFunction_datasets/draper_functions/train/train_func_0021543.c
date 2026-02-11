dock_check_find_docked_object_helper(object *objp, dock_function_info *infop)
{

	if (infop->parameter_variables.objp_value == objp)
	{
		infop->maintained_variables.bool_value = true;
		infop->early_return_condition = true;
	}
}
