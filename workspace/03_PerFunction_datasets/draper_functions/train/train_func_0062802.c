store(ObjectStream &st) const
{
	PUT_OBJECT(st, addr);

	PUT_OBJECT(st, addr_queue);
	PUT_INT32D(st, ops_parsed);
	PUT_BOOL(st, active);
	PUT_OBJECT(st, next_explored);
	PUT_OBJECT(st, first_explored);
	PUT_OBJECT(st, last_explored);
	PUT_INT32X(st, mode);
	PUT_OBJECT(st, explored);
	PUT_OBJECT(st, initialized);

	st.putComment("locations");
	PUTX_INT32D(st, getLocationCount(), "location_count");
	saveaddrs(st, locations);

	st.putComment("symbols");
	PUTX_INT32D(st, getSymbolCount(), "symbol_count");
	savelabels(st, symbols);

	PUT_OBJECT(st, analy_disasm);
	PUT_OBJECT(st, disasm);
	PUT_OBJECT(st, code);
	PUT_OBJECT(st, data);

	PUT_INT32D(st, location_threshold);
	PUT_INT32D(st, symbol_threshold);

	PUT_INT32D(st, max_opcode_length);

	if (cur_func) {
		PUTX_OBJECT(st, cur_func->addr, "cur_func");
	} else {
		PUTX_OBJECT(st, NULL, "cur_func");
	}

	dirty = false;
}
