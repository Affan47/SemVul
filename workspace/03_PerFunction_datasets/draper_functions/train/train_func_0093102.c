const_table_unsigned_value(const Const_table *c)
{
    switch(c->type) {
    case TYPE_INT:
        return (unsigned int)(c->val.i);
    case TYPE_CHAR:
	return (unsigned int)(c->val.ch);
    case TYPE_SHORT:
	return (unsigned int)(c->val.sh);
    case TYPE_UNSIGNED_CHAR:
	return (unsigned int)(c->val.uc);
    case TYPE_UNSIGNED_SHORT:
	return (unsigned int)(c->val.us);
    case TYPE_UNSIGNED:
	return c->val.ui;
    case TYPE_LONGLONG:
	if ((unsigned long long)c->val.ll <= UINT_MAX) {
	    return (unsigned int)(c->val.ll);
	} else {
	    warning("long long value '%lld' cannot be "
		    "represented in unsigned int\n", c->val.ll);
	    return (unsigned int)(c->val.ll);
	}
    case TYPE_UNSIGNED_LONGLONG:
	if (c->val.ull <= UINT_MAX) {
	    return (unsigned int)(c->val.ull);
	} else {
	    warning("unsigned long long value '%llu' "
		    "cannot be represented in int\n", c->val.ull);
	    return (unsigned int)(c->val.ull);
	}
    default:
        fatal("unexpected type: %s\n", str_type[c->type]);
        return UINT_MAX;
    }
}
