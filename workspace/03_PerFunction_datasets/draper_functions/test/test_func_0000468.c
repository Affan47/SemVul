mkomega(enum wakefulness wakefulness,
		  plan *p_, INT n, INT npad, INT ginv)
{
     plan_rdft *p = (plan_rdft *) p_;
     R *omega;
     INT i, gpower;
     trigreal scale;
     triggen *t;

     if ((omega = X(rader_tl_find)(n, npad + 1, ginv, omegas)))
	  return omega;

     omega = (R *)MALLOC(sizeof(R) * npad, TWIDDLES);

     scale = npad;

     t = X(mktriggen)(wakefulness, n);
     for (i = 0, gpower = 1; i < n-1; ++i, gpower = MULMOD(gpower, ginv, n)) {
	  trigreal w[2];
	  t->cexpl(t, gpower, w);
	  omega[i] = (w[0] + w[1]) / scale;
     }
     X(triggen_destroy)(t);
     A(gpower == 1);

     A(npad == n - 1 || npad >= 2*(n - 1) - 1);

     for (; i < npad; ++i)
	  omega[i] = K(0.0);
     if (npad > n - 1)
	  for (i = 1; i < n-1; ++i)
	       omega[npad - i] = omega[n - 1 - i];

     p->apply(p_, omega, omega);

     X(rader_tl_insert)(n, npad + 1, ginv, omega, &omegas);
     return omega;
}
