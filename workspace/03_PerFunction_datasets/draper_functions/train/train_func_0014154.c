ao_nparams(OPT *aod, const char *opt, int inst)
{
	struct ao_opt	*p;
	int		ret = 0;

	if (aod) {
		p = findopt(aod, opt);

		if (p && (p->aoo_flags & AOTAKEN) && (p->aoo_insts) &&
				(inst >= 0) && (inst < p->aoo_ninst)) {
			ret = p->aoo_insts[inst].aoi_nparam;
		}
	}

	return(ret);
}
