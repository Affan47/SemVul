gcgcef_checksum(CGCEf *cgcef) {
    if (cgcef) {
	if (cgcef->e_kind != CGCEF_K_CGCEF) {
	    seterr(ERROR_NOTCGCEF);
	}
	else if (!valid_class(cgcef->e_class)) {
	    seterr(ERROR_UNKNOWN_CLASS);
	}
	else {
	    return _cgcef_csum(cgcef);
	}
    }
    return 0L;
}
