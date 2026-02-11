ITR_isDOTNAME(tkitr_t *itr, int shift)
{
	int c = itr->c + shift;
	if(c < itr->e) {
		kTerm *tk = itr->ts[c];
		if(!Term_isDOT(tk)) return 0;
		if(TT_(tk) == TT_NAME || TT_(tk) == TT_UNAME ||
			TT_(tk) == TT_FUNCNAME || TT_(tk) == TT_UFUNCNAME) return 1;
	}
	return 0;
}
