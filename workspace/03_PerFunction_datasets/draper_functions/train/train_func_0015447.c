change_branch_administrator_add(change::pointer cp, string_ty *usr_name)
{
    cstate_ty       *cstate_data;
    meta_type         *type_p;
    string_ty       **spp;
    cstate_branch_administrator_list_ty *lp;
    size_t          j;

    trace(("change_branch_administrator_add(cp = %8.8lX, "
	"usr_name = \"%s\")\n{\n", (long)cp, usr_name->str_text));
    cstate_data = cp->cstate_get();
    assert(cstate_data->branch);
    if (!cstate_data->branch->administrator)
	cstate_data->branch->administrator =
            (cstate_branch_administrator_list_ty *)
    	    cstate_branch_administrator_list_type.alloc();
    lp = cstate_data->branch->administrator;


    for (j = 0; j < lp->length; ++j)
    {
	if (str_equal(usr_name, lp->list[j]))
	{
    	    trace(("}\n"));
    	    return;
	}
    }


    spp =
	(string_ty **)
	cstate_branch_administrator_list_type.list_parse
	(
    	    cstate_data->branch->administrator,
    	    &type_p
	);
    assert(type_p == &string_type);
    *spp = str_copy(usr_name);
    trace(("}\n"));
}
