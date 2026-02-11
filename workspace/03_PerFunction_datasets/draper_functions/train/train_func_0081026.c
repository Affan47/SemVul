equality(Var lhs, Var rhs, int case_matters)
{
    if (lhs.type == rhs.type) {
	switch (lhs.type) {
	case TYPE_CLEAR:
	    return 1;
	case TYPE_NONE:
	    return 1;
	case TYPE_INT:
	    return lhs.v.num == rhs.v.num;
	case TYPE_OBJ:
	    return lhs.v.obj == rhs.v.obj;
	case TYPE_ERR:
	    return lhs.v.err == rhs.v.err;
	case TYPE_STR:
	    if (lhs.v.str == rhs.v.str)
		return 1;
	    else if (case_matters)
		return !strcmp(lhs.v.str, rhs.v.str);
	    else
		return !mystrcasecmp(lhs.v.str, rhs.v.str);
	case TYPE_FLOAT:
	    if (lhs.v.fnum == rhs.v.fnum)
		return 1;
	    else
		return *(lhs.v.fnum) == *(rhs.v.fnum);
	case TYPE_LIST:
	    return listequal(lhs, rhs, case_matters);
	case TYPE_MAP:
	    return mapequal(lhs, rhs, case_matters);
	default:
	    panic("EQUALITY: Unknown value type");
	}
    }
    return 0;
}
