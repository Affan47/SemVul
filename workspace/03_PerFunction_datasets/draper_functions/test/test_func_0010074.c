_valid_subexp(const char *exp, char stop1, char stop2)
{
    register int x;
    int nsc = 0;
    int np;
    int tld = 0;

    for (x = 0; exp[x] && (exp[x] != stop1) && (exp[x] != stop2); ++x) {
        switch(exp[x]) {
	case '~':
            if(tld)
                return INVALID_SXP;
            if (stop1)
                return INVALID_SXP;
            if (!exp[x+1])
                return INVALID_SXP;
            if (!x)
                return INVALID_SXP;
            ++tld;

	case '*':
	case '?':
	case '$':
            ++nsc;
            break;
	case '[':
            ++nsc;
            if((!exp[++x]) || (exp[x] == ']'))
                return INVALID_SXP;
            for(; exp[x] && (exp[x] != ']'); ++x) {
                if(exp[x] == '\\' && !exp[++x])
                    return INVALID_SXP;
            }
            if(!exp[x])
                return INVALID_SXP;
            break;
	case '(':
            ++nsc;
	    if (stop1)
		return INVALID_SXP;
            np = -1;
            do {
                int t = _valid_subexp(&exp[++x], ')', '|');
                if(t == 0 || t == INVALID_SXP)
                    return INVALID_SXP;
                x+=t;
		if(!exp[x])
		    return INVALID_SXP;
		++np;
            } while (exp[x] == '|' );
	    if(np < 1)
		return INVALID_SXP;
            break;
	case ')':
	case '|':
	case ']':
            return INVALID_SXP;
	case '\\':
	    ++nsc;
            if(!exp[++x])
                return INVALID_SXP;
            break;
	default:
            break;
        }
    }
    if((!stop1) && (!nsc))
        return NON_SXP;
    return ((exp[x] == stop1 || exp[x] == stop2) ? x : INVALID_SXP);
}
