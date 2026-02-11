_cgcef_flag(unsigned *f, CGCEf_Cmd cmd, unsigned flags) {
    if (cmd == CGCEF_C_SET) {
	return *f |= flags;
    }
    if (cmd == CGCEF_C_CLR) {
	return *f &= ~flags;
    }
    seterr(ERROR_INVALID_CMD);
    return 0;
}
