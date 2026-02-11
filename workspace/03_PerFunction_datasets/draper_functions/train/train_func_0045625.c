get_file_revision(fstate_src_ty *orig_src,
    change_functor &bad_state)
{


    trace(("change_identifier_subset::get_file_revision_by_uuid(\"%s\")\n{\n",
	orig_src->file_name->str_text));
    assert(orig_src);
    get_cp();
    assert(cp);
    cstate_ty *cstate_data = cp->cstate_get();
    fstate_src_ty *result_src = 0;
    switch (cstate_data->state)
    {
#ifndef DEBUG
    default:
#endif
    case cstate_state_awaiting_development:
	bad_state(cp);
	trace(("}\n"));
	return file_revision("/dev/null", false);

    case cstate_state_completed:
	{


	    trace(("project = \"%s\"\n",
		project_name_get(pid.get_pp())->str_text));
	    project_file_roll_forward *hp = get_historian();
	    file_event *fep = hp->get_last(orig_src);
	    if (!fep)
	    {


	       	trace(("}\n"));
		return file_revision("/dev/null", false);
	    }
	    result_src = fep->get_src();
	}
	break;

    case cstate_state_being_integrated:
    case cstate_state_awaiting_integration:
    case cstate_state_being_reviewed:
    case cstate_state_awaiting_review:
    case cstate_state_being_developed:
	trace(("mark\n"));
	result_src = change_file_find(cp, orig_src, view_path_simple);
	if (!result_src)
	{
            sub_context_ty sc;
	    sc.var_set_string("File_Name", orig_src->file_name);
            change_fatal(cp, &sc, i18n("no $filename"));
	}
	break;
    }
    trace(("result_src = %08lX\n", (long)result_src));
    assert(result_src);
    switch (result_src->action)
    {
    case file_action_remove:


	trace(("}\n"));
	return file_revision("/dev/null", false);

    case file_action_create:
    case file_action_modify:
    case file_action_insulate:
    case file_action_transparent:
	break;
    }
    int from_unlink = 0;
    trace(("edit = %s\n", result_src->edit->revision->str_text));
    nstring from(change_file_version_path(cp, result_src, &from_unlink));
    trace(("}\n"));
    return file_revision(from, from_unlink);
}
