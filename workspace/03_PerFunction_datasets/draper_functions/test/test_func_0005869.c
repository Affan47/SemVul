completion_get(command_ty *)
{
    string_ty       *project_name;
    project_ty      *pp;
    complete_ty     *result;

    project_name = 0;
    arglex2_retable(0);
    arglex();
    while (arglex_token != arglex_token_eoln)
    {
	switch (arglex_token)
	{
	default:
	    result = generic_argument_complete();
	    if (result)
		return result;
	    continue;

	case arglex_token_change:
	    switch (arglex())
	    {
	    default:
		continue;

	    case arglex_token_number:
	    case arglex_token_number_incomplete:
	    case arglex_token_string_incomplete:
		break;
	    }
	    break;

	case arglex_token_number:
	case arglex_token_number_incomplete:
	    break;

	case arglex_token_project:
	    switch (arglex())
	    {
	    default:
		continue;

	    case arglex_token_string:
		project_name = str_from_c(arglex_value.alv_string);
		break;

	    case arglex_token_string_incomplete:
	    case arglex_token_number_incomplete:
		return complete_project_name();
	    }
	    break;

	case arglex_token_string:
	    project_name = str_from_c(arglex_value.alv_string);
	    break;

	case arglex_token_string_incomplete:
	    return complete_project_name();
	}
	arglex();
    }


    if (!project_name)
    {
        nstring n = user_ty::create()->default_project();
	project_name = str_copy(n.get_ref());
    }
    pp = project_alloc(project_name);
    str_free(project_name);
    pp->bind_existing();


    return complete_change_number(pp, (1 << cstate_state_being_developed));
}
