bf_tostr(Var arglist, Byte next, void *vdata, Objid progr)
{
    package p;
    Stream *s = new_stream(100);

    TRY_STREAM {
	Var r;
	int i;

	for (i = 1; i <= arglist.v.list[0].v.num; i++) {
	    stream_add_tostr(s, arglist.v.list[i]);
	}
	r.type = TYPE_STR;
	r.v.str = str_dup(stream_contents(s));
	p = make_var_pack(r);
    }
    EXCEPT (stream_too_big) {
	p = make_space_pack();
    }
    ENDTRY_STREAM;
    free_stream(s);
    free_var(arglist);
    return p;
}
