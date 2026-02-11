gnumeric_tdist (GnmFuncEvalInfo *ei, GnmValue const * const *argv)
{
	gnm_float x = value_get_as_float (argv[0]);
	gnm_float dof = value_get_as_float (argv[1]);
	gnm_float tails = value_get_as_float (argv[2]);
	gnm_float p;

	if (dof < 1)
		goto bad;

	if (tails == 1) {
		gboolean lower_tail = FALSE;
		if (x < 0) {
			lower_tail = TRUE;
			x = -x;
		}
		p = pt (x, dof, lower_tail, FALSE);
	} else if (tails == 2) {
		if (x < 0)
			goto bad;
		p = 2 * pt (x, dof, FALSE, FALSE);
	} else
		goto bad;

	return value_new_float (p);

 bad:
	return value_new_error_NUM (ei->pos);
}
