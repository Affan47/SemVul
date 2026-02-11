date__strptime(const char *str, size_t slen,
	       const char *fmt, size_t flen, VALUE hash)
{
    size_t si;
    VALUE cent, merid;

    si = date__strptime_internal(str, slen, fmt, flen, hash);

    if (slen > si) {
	VALUE s;

	s = rb_usascii_str_new(&str[si], slen - si);
	set_hash("leftover", s);
    }

    if (fail_p())
	return Qnil;

    cent = ref_hash("_cent");
    if (!NIL_P(cent)) {
	VALUE year;

	year = ref_hash("cwyear");
	if (!NIL_P(year))
	    set_hash("cwyear", f_add(year, f_mul(cent, INT2FIX(100))));
	year = ref_hash("year");
	if (!NIL_P(year))
	    set_hash("year", f_add(year, f_mul(cent, INT2FIX(100))));
	del_hash("_cent");
    }

    merid = ref_hash("_merid");
    if (!NIL_P(merid)) {
	VALUE hour;

	hour = ref_hash("hour");
	if (!NIL_P(hour)) {
	    hour = f_mod(hour, INT2FIX(12));
	    set_hash("hour", f_add(hour, merid));
	}
	del_hash("_merid");
    }

    return hash;
}
