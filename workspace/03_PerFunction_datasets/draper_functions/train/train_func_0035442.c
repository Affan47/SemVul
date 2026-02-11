adjust_dam(struct player *p, int type, int dam, aspect dam_aspect, int resist)
{
	const struct gf_type *gf_ptr = &gf_table[type];
	int i, denom;

	if (resist == 3)
		return 0;


	if ((type == GF_ACID && minus_ac(p)) || type == GF_HOLY_ORB)
		dam = (dam + 1) / 2;

	if (resist == -1)
		return (dam * 4 / 3);


	switch (dam_aspect) {
		case MINIMISE:
			denom = randcalc(gf_ptr->denom, 0, MAXIMISE);
			break;
		case MAXIMISE:
			denom = randcalc(gf_ptr->denom, 0, MINIMISE);
			break;
		default:
			denom = randcalc(gf_ptr->denom, 0, dam_aspect);
	}

	for (i = resist; i > 0; i--)
		if (denom)
			dam = dam * gf_ptr->num / denom;

	return dam;
}
