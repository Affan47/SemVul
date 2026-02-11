range_cover(VALUE range, VALUE val)
{
    VALUE beg, end;

    beg = RANGE_BEG(range);
    end = RANGE_END(range);
    if (r_le(beg, val)) {
	if (EXCL(range)) {
	    if (r_lt(val, end))
		return Qtrue;
	}
	else {
	    if (r_le(val, end))
		return Qtrue;
	}
    }
    return Qfalse;
}
