command_line_parse(void (*usage)(void))
{
    trace(("project_identifier_subset_plain::command_line_parse()\n{\n"));
    switch (arglex_token)
    {
    default:
	fatal_raw
	(
	    "%s: %d: option %s not handled in switch (bug)",
	    __FILE__,
	    __LINE__,
	    arglex_token_name(arglex_token)
	);


    case arglex_token_branch:
    case arglex_token_trunk:
    case arglex_token_grandparent:
	bad_argument(usage);


    case arglex_token_project:
	arglex();


    case arglex_token_string:
	arglex_parse_project(&project_name, usage);
	trace(("}\n"));
	return;
    }
    arglex();
    trace(("}\n"));
}
