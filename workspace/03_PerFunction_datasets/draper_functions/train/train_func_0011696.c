qf_mark_adjust(line1, line2, inc)
	linenr_t	line1;
	linenr_t	line2;
	long		inc;
{
	register int i;
	struct qf_line *qfp;

	if (qf_count)
		for (i = 0, qfp = qf_start; i < qf_count; ++i, qfp = qfp->qf_next)
			if (qfp->qf_fnum == curbuf->b_fnum &&
							qfp->qf_lnum >= line1 && qfp->qf_lnum <= line2)
			{
				if (inc == MAXLNUM)
					qfp->qf_cleared = TRUE;
				else
					qfp->qf_lnum += inc;
			}
}
