iso8601_ext_time_cb(VALUE m, VALUE hash)
{
    VALUE s[SNUM + 1];

    {
	int i;
	s[0] = Qnil;
	for (i = 1; i <= SNUM; i++)
	    s[i] = rb_reg_nth_match(i, m);
    }

    set_hash("hour", str2num(s[1]));
    set_hash("min", str2num(s[2]));
    if (!NIL_P(s[3]))
	set_hash("sec", str2num(s[3]));
    if (!NIL_P(s[4]))
	set_hash("sec_fraction", sec_fraction(s[4]));
    if (!NIL_P(s[5])) {
	set_hash("zone", s[5]);
	set_hash("offset", date_zone_to_diff(s[5]));
    }

    return 1;
}
