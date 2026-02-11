r_t_plural(struct SN_env * z) {
    int among_var;
    {	int m3;
	int m = z->l - z->c; (void) m;
	if (z->c < z->I[0]) return 0;
	z->c = z->I[0];
	m3 = z->lb; z->lb = z->c;
	z->c = z->l - m;
	z->ket = z->c;
	if (!(eq_s_b(z, 1, s_13))) { z->lb = m3; return 0; }
	z->bra = z->c;
	{   int m_test = z->l - z->c;
	    if (!(in_grouping_b_U(z, g_V1, 97, 246))) { z->lb = m3; return 0; }
	    z->c = z->l - m_test;
	}
	{   int ret;
	    ret = slice_del(z);
	    if (ret < 0) return ret;
	}
	z->lb = m3;
    }
    {	int m3;
	int m = z->l - z->c; (void) m;
	if (z->c < z->I[1]) return 0;
	z->c = z->I[1];
	m3 = z->lb; z->lb = z->c;
	z->c = z->l - m;
	z->ket = z->c;
	among_var = find_among_b(z, a_9, 2);
	if (!(among_var)) { z->lb = m3; return 0; }
	z->bra = z->c;
	z->lb = m3;
    }
    switch(among_var) {
	case 0: return 0;
	case 1:
	    {	int m = z->l - z->c; (void) m;
		if (!(eq_s_b(z, 2, s_14))) goto lab0;
		return 0;
	    lab0:
		z->c = z->l - m;
	    }
	    break;
    }
    {	int ret;
	ret = slice_del(z);
	if (ret < 0) return ret;
    }
    return 1;
}
