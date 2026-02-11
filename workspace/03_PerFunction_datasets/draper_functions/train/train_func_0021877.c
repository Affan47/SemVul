softingcs_find_platform_data(unsigned int manf, unsigned int prod)
{
	const struct softing_platform_data *lp;

	for (lp = softingcs_platform_data; lp->manf; ++lp) {
		if ((lp->manf == manf) && (lp->prod == prod))
			return lp;
	}
	return NULL;
}
