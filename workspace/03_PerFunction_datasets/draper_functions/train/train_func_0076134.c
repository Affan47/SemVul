get_frame_ptr(object x)
{
	frame_ptr p;

	if (type_of(x) != t_fixnum)
		goto ILLEGAL;
	p = frs_org + fix(x);
	if (fix(x)==0) return p;
	if (frs_org <= p && p <= frs_top)
		return(p);
ILLEGAL:
	FEerror("~S is an illegal frs index.", 1, x);
	return NULL;
}
