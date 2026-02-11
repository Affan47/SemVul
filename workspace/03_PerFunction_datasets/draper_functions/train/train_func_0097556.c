rb_str_modify_expand(VALUE str, long expand)
{
    if (expand < 0) {
	rb_raise(rb_eArgError, "negative expanding string size");
    }
    if (!str_independent(str)) {
	str_make_independent_expand(str, expand);
    }
    else if (expand > 0) {
	long len = RSTRING_LEN(str);
	long capa = len + expand;
	if (!STR_EMBED_P(str)) {
	    REALLOC_N(RSTRING(str)->as.heap.ptr, char, capa+1);
	    STR_UNSET_NOCAPA(str);
	    RSTRING(str)->as.heap.aux.capa = capa;
	}
	else if (capa > RSTRING_EMBED_LEN_MAX) {
	    str_make_independent_expand(str, expand);
	}
    }
    ENC_CODERANGE_CLEAR(str);
}
