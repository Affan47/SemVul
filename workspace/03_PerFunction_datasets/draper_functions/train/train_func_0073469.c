gcgcef_msize(CGCEf *cgcef, CGCEf_Type type, size_t count, unsigned ver) {
    size_t n;

    if (cgcef) {
	if (cgcef->e_kind != CGCEF_K_CGCEF) {
	    seterr(ERROR_NOTCGCEF);
	}
	else if (!valid_class(cgcef->e_class)) {
	    seterr(ERROR_UNKNOWN_CLASS);
	}
	else if (!valid_version(ver)) {
	    seterr(ERROR_UNKNOWN_VERSION);
	}
	else if (!valid_type(type)) {
	    seterr(ERROR_UNKNOWN_TYPE);
	}
	else if (!(n = _msize(cgcef->e_class, ver, type))) {
	    seterr(ERROR_UNKNOWN_TYPE);
	}
	else {
	    return count * n;
	}
    }
    return 0;
}
