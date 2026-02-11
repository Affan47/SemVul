r_possessive(struct SN_env * z) {
    int among_var;
    {	int m3;
	int m = z->l - z->c; (void) m;
	if (z->c < z->I[0]) return 0;
	z->c = z->I[0];
	m3 = z->lb; z->lb = z->c;
	z->c = z->l - m;
	z->ket = z->c;
	among_var = find_among_b(z, a_4, 9);
	if (!(among_var)) { z->lb = m3; return 0; }
	z->bra = z->c;
	z->lb = m3;
    }
    switch(among_var) {
	case 0: return 0;
	case 1:
	    {	int m = z->l - z->c; (void) m;
		if (!(eq_s_b(z, 1, s_0))) goto lab0;
		return 0;
	    lab0:
		z->c = z->l - m;
	    }
	    {	int ret;
		ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 2:
	    {	int ret;
		ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    z->ket = z->c;
	    if (!(eq_s_b(z, 3, s_1))) return 0;
	    z->bra = z->c;
	    {	int ret;
		ret = slice_from_s(z, 3, s_2);
		if (ret < 0) return ret;
	    }
	    break;
	case 3:
	    {	int ret;
		ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 4:
	    if (!(find_among_b(z, a_1, 6))) return 0;
	    {	int ret;
		ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 5:
	    if (!(find_among_b(z, a_2, 6))) return 0;
	    {	int ret;
		ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 6:
	    if (!(find_among_b(z, a_3, 2))) return 0;
	    {	int ret;
		ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
    }
    return 1;
}
