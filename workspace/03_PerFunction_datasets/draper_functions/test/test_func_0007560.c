combcol_sizeof(combcol *cc)
{
	u_long	tot = 0L;
	combelm	*ce;

	tot += sizeof(combcol);
	for(ce=cc->elements; ce!=NULL; ce=ce->next)
		tot += combelm_sizeof(ce);

	return tot;
}
