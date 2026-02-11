applicable(const S *ego, rdft_kind kind,
		      INT r, INT rs,
		      INT m, INT ms,
		      INT v, INT vs,
		      R *cr, R *ci,
		      const planner *plnr, INT *extra_iter)
{
     if (ego->bufferedp) {
	  if (!applicable0_buf(ego, kind, r, rs, m, ms, v, vs, cr, ci, plnr,
			       extra_iter))
	       return 0;
     } else {
	  if (!applicable0(ego, kind, r, rs, m, ms, v, vs, cr, ci, plnr,
			   extra_iter))
	       return 0;
     }

     if (NO_UGLYP(plnr) && X(ct_uglyp)((ego->bufferedp? (INT)512 : (INT)16),
				       v, m * r, r))
	  return 0;

     return 1;
}
