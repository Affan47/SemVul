bf_trunc(Var arglist, Byte next, void *vdata, Objid progr)
{
    double d;

    d = *arglist.v.list[1].v.fnum;
    errno = 0;
    if (d < 0.0)
	d = ceil(d);
    else
	d = floor(d);
    free_var(arglist);
    if (errno == EDOM)
	return make_error_pack(E_INVARG);
    else if (errno != 0 || !IS_REAL(d))
	return make_error_pack(E_FLOAT);
    else
	return make_var_pack(new_float(d));
}
