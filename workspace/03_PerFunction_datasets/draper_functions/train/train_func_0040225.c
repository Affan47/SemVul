httpHdrRangeRespSpecParseInit(HttpHdrRangeSpec * spec, const char *field, int flen)
{
    const char *p;
    assert(spec);
    spec->offset = spec->length = range_spec_unknown;
    if (flen < 2)
	return 0;

    if (*field == '*')
	return 1;

    if (!((p = strchr(field, '-')) && (p - field < flen))) {
	debug(68, 2) ("invalid (no '-') resp-range-spec near: '%s'\n", field);
	return 0;
    }

    if (!httpHeaderParseSize(field, &spec->offset))
	return 0;
    p++;

    if (p - field < flen) {
	squid_off_t last_pos;
	if (!httpHeaderParseSize(p, &last_pos))
	    return 0;
	spec->length = size_diff(last_pos + 1, spec->offset);
    }

    if (known_spec(spec->length) && !spec->length) {
	debug(68, 2) ("invalid range (%ld += %ld) in resp-range-spec near: '%s'\n",
	    (long int) spec->offset, (long int) spec->length, field);
	return 0;
    }
    return 1;
}
