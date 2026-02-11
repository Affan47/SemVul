rb_ary_splice(VALUE ary, long beg, long len, VALUE rpl)
{
    long rlen;

    if (len < 0) rb_raise(rb_eIndexError, "negative length (%ld)", len);
    if (beg < 0) {
	beg += RARRAY_LEN(ary);
	if (beg < 0) {
	    rb_raise(rb_eIndexError, "index %ld too small for array; minimum: %ld",
		     beg - RARRAY_LEN(ary), -RARRAY_LEN(ary));
	}
    }
    if (RARRAY_LEN(ary) < len || RARRAY_LEN(ary) < beg + len) {
	len = RARRAY_LEN(ary) - beg;
    }

    if (rpl == Qundef) {
	rlen = 0;
    }
    else {
	rpl = rb_ary_to_ary(rpl);
	rlen = RARRAY_LEN(rpl);
    }
    rb_ary_modify(ary);
    if (beg >= RARRAY_LEN(ary)) {
	if (beg > ARY_MAX_SIZE - rlen) {
	    rb_raise(rb_eIndexError, "index %ld too big", beg);
	}
	len = beg + rlen;
	if (len >= ARY_CAPA(ary)) {
	    ary_double_capa(ary, len);
	}
	rb_mem_clear(RARRAY_PTR(ary) + RARRAY_LEN(ary), beg - RARRAY_LEN(ary));
	if (rlen > 0) {
	    MEMCPY(RARRAY_PTR(ary) + beg, RARRAY_PTR(rpl), VALUE, rlen);
	}
	ARY_SET_LEN(ary, len);
    }
    else {
	long alen;

	alen = RARRAY_LEN(ary) + rlen - len;
	if (alen >= ARY_CAPA(ary)) {
	    ary_double_capa(ary, alen);
	}

	if (len != rlen) {
	    MEMMOVE(RARRAY_PTR(ary) + beg + rlen, RARRAY_PTR(ary) + beg + len,
		    VALUE, RARRAY_LEN(ary) - (beg + len));
	    ARY_SET_LEN(ary, alen);
	}
	if (rlen > 0) {
	    MEMMOVE(RARRAY_PTR(ary) + beg, RARRAY_PTR(rpl), VALUE, rlen);
	}
    }
}
