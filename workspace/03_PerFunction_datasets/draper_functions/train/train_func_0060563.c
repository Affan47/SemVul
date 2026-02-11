run_inner(server_ty *sp, string_ty *)
    const
{
    size_t          j;

    if (server_root_required(sp, "remove"))
	return;
    if (server_directory_required(sp, "remove"))
	return;


    module_ty::options opt;
    for (j = 0; j < sp->np->argument_count(); ++j)
    {
	string_ty *arg = sp->np->argument_nth(j);
	if (arg->str_text[0] != '-')
	    break;
	if (0 == strcmp(arg->str_text, "--"))
	{
	    ++j;
	    break;
	}
	switch (arg->str_text[1])
	{
	case 'f':


	    opt.f++;
	    break;

	case 'l':


	    opt.l++;
	    break;

	case 'R':


	    opt.R++;
	    break;

	default:
	    server_e(sp, "remove: unknown '%s' option", arg->str_text);
	    break;
	}
    }


    bool ok = true;
    directory_ty *dp = sp->np->get_curdir();
    for (; j < sp->np->argument_count(); ++j)
    {
	string_ty       *arg;
	string_ty       *client_side;
	string_ty       *server_side;


	arg = sp->np->argument_nth(j);
	client_side = os_path_cat(dp->client_side, arg);
	server_side = os_path_cat(dp->server_side, arg);


	if (sp->np->directory_find_client_side(client_side))
	{
	    server_m
	    (
		sp,
		"Directory " ROOT_PATH "/%s removed from the repository "
		    "(ignored)",
		server_side->str_text
	    );
	    str_free(client_side);
	    str_free(server_side);
	    continue;
	}


	module mp = module::find_trim(server_side);
	if (!mp->remove(sp, client_side, server_side, opt))
	    ok = false;
	str_free(client_side);
	str_free(server_side);


	if (!ok)
	    break;
    }

    if (ok)
    {
	server_e(sp, "use 'cvs commit' to make the 'cvs remove' permanent");
	server_ok(sp);
    }
}
