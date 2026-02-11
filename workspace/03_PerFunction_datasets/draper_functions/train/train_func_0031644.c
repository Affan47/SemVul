new_change_undo_main(void)
{
    string_ty	    *project_name;
    long	    change_number;
    project_ty	    *pp;
    user_ty::pointer up;
    change::pointer cp;
    cstate_ty	    *cstate_data;

    trace(("new_change_undo_main()\n{\n"));
    arglex();
    project_name = 0;
    change_number = 0;
    while (arglex_token != arglex_token_eoln)
    {
	switch (arglex_token)
	{
	default:
	    generic_argument(new_change_undo_usage);
	    continue;

	case arglex_token_change:
	    arglex();


	case arglex_token_number:
	    arglex_parse_change
	    (
		&project_name,
		&change_number,
		new_change_undo_usage
	    );
	    continue;

	case arglex_token_project:
	    arglex();


	case arglex_token_string:
	    arglex_parse_project(&project_name, new_change_undo_usage);
	    continue;

	case arglex_token_wait:
	case arglex_token_wait_not:
	    user_ty::lock_wait_argument(new_change_undo_usage);
	    break;
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


    up = user_ty::create();


    if (!change_number)
	change_number = up->default_change(pp);
    cp = change_alloc(pp, change_number);
    change_bind_existing(cp);


    pp->pstate_lock_prepare();
    change_cstate_lock_prepare(cp);
    lock_take();
    cstate_data = cp->cstate_get();


    if (cstate_data->state != cstate_state_awaiting_development)
	change_fatal(cp, 0, i18n("bad ncu state"));
    if
    (
	!project_administrator_query(pp, up->name())
    &&
	nstring(change_creator_name(cp)) != up->name()
    )
	project_fatal(pp, 0, i18n("not an administrator"));


    project_change_delete(pp, change_number);


    project_become(pp);
    commit_unlink_errok(change_cstate_filename_get(cp));
    commit_unlink_errok(change_fstate_filename_get(cp));
    project_become_undo(pp);


    pp->pstate_write();
    commit();
    lock_release();


    change_verbose(cp, 0, i18n("new change undo complete"));
    change_free(cp);
    project_free(pp);
    trace(("}\n"));
}
