lseg_intersect_internal(LSEG *l1, LSEG *l2)
{
	LINE		ln;
	Point	   *interpt;
	bool		retval;

	line_construct_pts(&ln, &l2->p[0], &l2->p[1]);
	interpt = interpt_sl(l1, &ln);

	if (interpt != NULL && on_ps_internal(interpt, l2))
		retval = true;
	else
		retval = false;
	return retval;
}
