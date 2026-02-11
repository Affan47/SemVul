compute_man_ptrans(
scanrd_ *s,
double *sfid
) {
	int rv;


	rv = calc_ptrans(s, sfid, s->fid);
	if (rv == 0)
		rv = invert_ptrans(s->iptrans, s->ptrans);

	return rv;
}
