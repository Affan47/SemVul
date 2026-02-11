bf_move(Var arglist, Byte next, void *vdata, Objid progr)
{
    struct bf_move_data *data = vdata;
    package p;

    if (next == 1) {
	data = alloc_data(sizeof(*data));
	data->what = arglist.v.list[1].v.obj;
	data->where = arglist.v.list[2].v.obj;
    }
    p = do_move(arglist, next, data, progr);
    free_var(arglist);

    if (p.kind != BI_CALL)
	free_data(data);

    return p;
}
