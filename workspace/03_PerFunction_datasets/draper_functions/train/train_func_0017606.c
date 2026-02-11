const_table_longlong_value(const Const_table *c)
{
    switch(c->type) {
    case TYPE_INT:
	return (long long)c->val.i;
    case TYPE_CHAR:
	return (long long)(c->val.ch);
    case TYPE_SHORT:
	return (long long)(c->val.sh);
    case TYPE_UNSIGNED_CHAR:
	return (long long)(c->val.uc);
    case TYPE_UNSIGNED_SHORT:
	return (long long)(c->val.us);
    case TYPE_UNSIGNED:
	return (long long)(c->val.ui);
    case TYPE_LONGLONG:
	return (long long)(c->val.ll);
    case TYPE_UNSIGNED_LONGLONG:
	if (c->val.ull <= LLONG_MAX) {
	    return (long long)(c->val.ull);
	} else {
	    warning("unsigned long long value '%llu' "
		    "cannot be represented in long long\n", c->val.ull);
	    return (long long)(c->val.ull);
	}
    default:
        fatal("unexpected type: %s\n", str_type[c->type]);
        return LLONG_MAX;
    }
}
