bf_parse_json(Var arglist, Byte next, void *vdata, Objid progr)
{
    yajl_handle hand;
    yajl_parser_config cfg = { 1, 1 };
    yajl_status stat;

    struct parse_context pctx;
    pctx.top = &pctx.stack;
    pctx.stack.v.type = TYPE_INT;
    pctx.stack.v.v.num = 0;
    pctx.mode = MODE_COMMON_SUBSET;

    const char *str = arglist.v.list[1].v.str;
    size_t len = strlen(str);

    package pack;

    int done = 0;

    if (1 < arglist.v.list[0].v.num) {
	if (!mystrcasecmp(arglist.v.list[2].v.str, "common-subset")) {
	    pctx.mode = MODE_COMMON_SUBSET;
	} else if (!mystrcasecmp(arglist.v.list[2].v.str, "embedded-types")) {
	    pctx.mode = MODE_EMBEDDED_TYPES;
	} else {
	    free_var(arglist);
	    return make_error_pack(E_INVARG);
	}
    }

    hand = yajl_alloc(&callbacks, &cfg, NULL, (void *)&pctx);

    while (!done) {
	if (len == 0)
	    done = 1;

	if (done)
	    stat = yajl_parse_complete(hand);
	else
	    stat = yajl_parse(hand, str, len);

	len = 0;

	if (done) {
	    if (stat != yajl_status_ok) {

		while (pctx.top != &pctx.stack) {
		    Var v = POP(pctx.top);
		    free_var(v);
		}
		pack = make_error_pack(E_INVARG);
	    } else {
		Var v = POP(pctx.top);
		pack = make_var_pack(v);
	    }
	}
    }

    yajl_free(hand);

    free_var(arglist);
    return pack;
}
