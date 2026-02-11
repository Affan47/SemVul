prepare() {
	int r = 0;
	if ((r = parse_decls()))
		return r;
	if ((r = prepare_ir()))
		return r;
	return 0;
}
