r_plural(struct SN_env * z) {
    int among_var;
    z->ket = z->c;
    if (z->c <= z->lb || z->p[z->c - 1] != 107) return 0;
    among_var = find_among_b(z, a_8, 7);
    if (!(among_var)) return 0;
    z->bra = z->c;
    {	int ret = r_R1(z);
	if (ret == 0) return 0;
	if (ret < 0) return ret;
    }
    switch(among_var) {
	case 0: return 0;
	case 1:
	    {	int ret = slice_from_s(z, 1, s_7);
		if (ret < 0) return ret;
	    }
	    break;
	case 2:
	    {	int ret = slice_from_s(z, 1, s_8);
		if (ret < 0) return ret;
	    }
	    break;
	case 3:
	    {	int ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 4:
	    {	int ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 5:
	    {	int ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 6:
	    {	int ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
	case 7:
	    {	int ret = slice_del(z);
		if (ret < 0) return ret;
	    }
	    break;
    }
    return 1;
}
