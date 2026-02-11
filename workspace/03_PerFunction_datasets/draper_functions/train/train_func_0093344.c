applicable0_buf(const S *ego, rdft_kind kind,
			   INT r, INT rs,
			   INT m, INT ms,
			   INT v, INT vs,
			   const R *cr, const R *ci,
			   const planner *plnr, INT *extra_iter)
{
     const hc2c_desc *e = ego->desc;
     INT batchsz, brs;
     UNUSED(v); UNUSED(rs); UNUSED(ms); UNUSED(vs);

     return (
	  1
	  && r == e->radix
	  && kind == e->genus->kind


	  && (cr = (const R *)0, ci = cr + 1,
	      batchsz = compute_batchsize(r),
	      brs = 4 * batchsz, 1)

	  && e->genus->okp(cr, ci, cr + brs - 2, ci + brs - 2,
			   brs, 1, 1+batchsz, 2, plnr)

	  && ((*extra_iter = 0,
	       e->genus->okp(cr, ci, cr + brs - 2, ci + brs - 2,
			     brs, 1, 1 + (((m-1)/2) % batchsz), 2, plnr))
	      ||
	      (*extra_iter = 1,
	       e->genus->okp(cr, ci, cr + brs - 2, ci + brs - 2,
			     brs, 1, 1 + 1 + (((m-1)/2) % batchsz), 2, plnr)))

	  );
}
