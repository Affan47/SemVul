bf_verb_info(Var arglist, Byte next, void *vdata, Objid progr)
{
    Objid oid = arglist.v.list[1].v.obj;
    Var desc = arglist.v.list[2];
    db_verb_handle h;
    Var r;
    unsigned flags;
    char *s;
    enum error e;

    if ((e = validate_verb_descriptor(desc)) != E_NONE
	|| (e = E_INVARG, !valid(oid))) {
	free_var(arglist);
	return make_error_pack(e);
    }
    h = find_described_verb(oid, desc);
    free_var(arglist);

    if (!h.ptr)
	return make_error_pack(E_VERBNF);
    else if (!db_verb_allows(h, progr, VF_READ))
	return make_error_pack(E_PERM);

    r = new_list(3);
    r.v.list[1].type = TYPE_OBJ;
    r.v.list[1].v.obj = db_verb_owner(h);
    r.v.list[2].type = TYPE_STR;
    r.v.list[2].v.str = s = str_dup("xxxx");
    flags = db_verb_flags(h);
    if (flags & VF_READ)
	*s++ = 'r';
    if (flags & VF_WRITE)
	*s++ = 'w';
    if (flags & VF_EXEC)
	*s++ = 'x';
    if (flags & VF_DEBUG)
	*s++ = 'd';
    *s = '\0';
    r.v.list[3].type = TYPE_STR;
    r.v.list[3].v.str = str_ref(db_verb_names(h));

    return make_var_pack(r);
}
