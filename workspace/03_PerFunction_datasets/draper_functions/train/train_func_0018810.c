bf_set_prop_info(Var arglist, Byte next, void *vdata, Objid progr)
{
    Objid oid = arglist.v.list[1].v.obj;
    const char *pname = arglist.v.list[2].v.str;
    Var info = arglist.v.list[3];
    enum error e = set_prop_info(oid, pname, info, progr);

    free_var(arglist);
    if (e == E_NONE)
	return no_var_pack();
    else
	return make_error_pack(e);
}
