par_touch(GcxPar p)
{
	GcxPar pp;

	PAR(p)->flags |= (PAR_TO_SAVE | PAR_USER);

	pp = PAR(p)->parent;
	while (pp != PAR_NULL) {
		PAR(pp)->flags |= (PAR_TO_SAVE | PAR_USER);
		pp = PAR(pp)->parent;
	}
}
