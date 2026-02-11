list(void)
{
    string_ty *ifn = 0;
    string_ty *ofn = 0;
    arglex();
    while (arglex_token != arglex_token_eoln)
    {
	switch (arglex_token)
	{
	default:
	    generic_argument(usage);
	    continue;

	case arglex_token_file:
	    if (ifn)
		duplicate_option(usage);
	    switch (arglex())
	    {
	    default:
		option_needs_file(arglex_token_file, usage);


	    case arglex_token_stdio:
		ifn = str_from_c("");
		break;

	    case arglex_token_string:
		ifn = str_from_c(arglex_value.alv_string);
		break;
	    }
	    break;

	case arglex_token_output:
	    if (ofn)
		duplicate_option(usage);
	    switch (arglex())
	    {
	    default:
		option_needs_file(arglex_token_output, usage);


	    case arglex_token_stdio:
		ofn = str_from_c("");
		break;

	    case arglex_token_string:
		ofn = str_from_c(arglex_value.alv_string);
		break;
	    }
	    break;
	}
	arglex();
    }


    patch_list_ty *plp = patch_slurp(ifn);
    assert(plp);


    output::pointer ofp = output_file::text_open(ofn);
    for (size_t j = 0; j < plp->length; ++j)
    {
	assert(plp->item[j]);
	assert(plp->item[j]->name.nstrings);
	assert(plp->item[j]->name.string[0]);
	ofp->fputs(plp->item[j]->name.string[0]);
	ofp->fputc('\n');
    }
}
