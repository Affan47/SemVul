bf_length(Var arglist, Byte next, void *vdata, Objid progr)
{
    Var r;
    switch (arglist.v.list[1].type) {
    case TYPE_LIST:
	r.type = TYPE_INT;
	r.v.num = arglist.v.list[1].v.list[0].v.num;
	break;
    case TYPE_MAP:
	r.type = TYPE_INT;
	r.v.num = maplength(arglist.v.list[1]);
	break;
    case TYPE_STR:
	r.type = TYPE_INT;
	r.v.num = memo_strlen(arglist.v.list[1].v.str);
	break;
    default:
	free_var(arglist);
	return make_error_pack(E_TYPE);
	break;
    }

    free_var(arglist);
    return make_var_pack(r);
}
