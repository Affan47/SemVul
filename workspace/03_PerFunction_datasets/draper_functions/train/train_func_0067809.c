bf_add_verb(Var arglist, Byte next, void *vdata, Objid progr)
{
    Objid oid = arglist.v.list[1].v.obj;
    Var info = arglist.v.list[2];
    Var args = arglist.v.list[3];
    Var result;
    Objid owner;
    unsigned flags;
    const char *names;
    db_arg_spec dobj, iobj;
    db_prep_spec prep;
    enum error e;

    if ((e = validate_verb_info(info, &owner, &flags, &names)) != E_NONE)
	 ;
    else if ((e = validate_verb_args(args, &dobj, &prep, &iobj)) != E_NONE)
	free_str(names);
    else if (!valid(oid)) {
	free_str(names);
	e = E_INVARG;
    } else if (!db_object_allows(oid, progr, FLAG_WRITE)
	       || (progr != owner && !is_wizard(progr))) {
	free_str(names);
	e = E_PERM;
    } else {
	result.type = TYPE_INT;
	result.v.num = db_add_verb(oid, names, owner, flags, dobj, prep, iobj);
    }

    free_var(arglist);
    if (e == E_NONE)
	return make_var_pack(result);
    else
	return make_error_pack(e);
}
