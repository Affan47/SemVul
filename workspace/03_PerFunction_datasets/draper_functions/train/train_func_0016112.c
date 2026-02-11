code_flow(const String &flow_code, int port, bool isoutput,
		       Bitvector *bv, int size, ErrorHandler *errh)
{
    if (port < 0 || size == 0) {
	bv->assign(size, false);
	return 0;
    } else if (!flow_code || flow_code.equals("x/x", 3)) {
	bv->assign(size, true);
	return 0;
    } else
	bv->assign(size, false);

    const char *fbegin[2], *fend[2], *slash = find(flow_code, '/');
    fbegin[end_to] = flow_code.begin();
    if (slash == flow_code.end()) {
	fbegin[end_from] = fbegin[end_to];
	fend[end_to] = fend[end_from] = flow_code.end();
    } else if (slash + 1 == flow_code.end() || slash[1] == '/')
	return (errh ? errh->error("flow code: bad %</%>") : -1);
    else {
	fend[end_to] = slash;
	fbegin[end_from] = slash + 1;
	fend[end_from] = flow_code.end();
    }

    Bitvector source_code, sink_code;

    for (int i = 0; i < port; ++i)
	skip_flow_code(fbegin[isoutput], fend[isoutput]);
    next_flow_code(fbegin[isoutput], fend[isoutput], port, source_code, errh);

    for (int i = 0; i < size; i++) {
	next_flow_code(fbegin[!isoutput], fend[!isoutput], i, sink_code, errh);
	if (source_code.nonzero_intersection(sink_code))
	    (*bv)[i] = true;
    }

    return 0;
}
