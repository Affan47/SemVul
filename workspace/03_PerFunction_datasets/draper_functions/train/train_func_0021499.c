r_postlude(struct SN_env * z) {
    if (!(z->B[0])) return 0;
    while(1) {
	int c = z->c;
	while(1) {
	    int c = z->c;
	    z->bra = z->c;
	    if (!(eq_s(z, 1, s_48))) goto lab1;
	    z->ket = z->c;
	    z->c = c;
	    break;
	lab1:
	    z->c = c;
	    {	int c = skip_utf8(z->p, z->c, 0, z->l, 1);
		if (c < 0) goto lab0;
		z->c = c;
	    }
	}
	{   int ret;
	    ret = slice_from_s(z, 1, s_49);
	    if (ret < 0) return ret;
	}
	continue;
    lab0:
	z->c = c;
	break;
    }
    return 1;
}
