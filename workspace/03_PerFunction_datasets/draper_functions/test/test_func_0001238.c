lam_F_free_hdl(int index)
{
	void		**p;

	if (index < LAM_MAXF77PREDEF) return;

	p = lam_F_handles + index;
	*p = 0;
	--lam_F_nhdl;

	if (index == lam_F_maxhdl) {
		for (--lam_F_maxhdl, --p;
				lam_F_maxhdl >= 0; --lam_F_maxhdl, --p) {
			if (*p) break;
		}
	}
}
