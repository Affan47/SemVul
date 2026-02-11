ojc_aget(ojcVal val, const char **path) {
    ojcVal	m;

    if (0 == path || 0 == val || 0 == *path) {
	return val;
    }
    switch (val->type) {
    case OJC_ARRAY:
	{
	    unsigned int	index = 0;
	    const char		*p;

	    for (p = *path; '\0' != *p; p++) {
		if (*p < '0' || '9' < *p) {
		    return 0;
		}
		index = index * 10 + (int)(*p - '0');
		if (MAX_INDEX < index) {
		    return 0;
		}
	    }
	    for (m = val->members.head; 0 < index; m = m->next, index--) {
		if (0 == m) {
		    return 0;
		}
	    }
	    return ojc_aget(m, path + 1);
	}
    case OJC_OBJECT:
	{
	    const char	*key;

	    for (m = val->members.head; ; m = m->next) {
		if (0 == m) {
		    return 0;
		}
		switch (m->key_type) {
		case STR_PTR:	key = m->key.str;	break;
		case STR_ARRAY:	key = m->key.ca;	break;
		case STR_BLOCK:	key = m->key.bstr->ca;	break;
		case STR_NONE:
		default:	key = 0;		break;
		}
		if (0 != key && 0 == strcmp(*path, key)) {
		    return ojc_aget(m, path + 1);
		}
	    }
	    break;
	}
    default:
	break;
    }
    return 0;
}
