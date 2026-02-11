accuracy_test(dofft_closure *k, aconstrain constrain,
		   int sign, int n, C *a, C *b, int rounds, int impulse_rounds,
		   double t[6])
{
     int r, i;
     int ntests = 0;
     bench_complex czero = {0, 0};

     for (i = 0; i < 6; ++i) t[i] = 0.0;

     for (r = 0; r < rounds; ++r) {
	  arand(a, n);
	  if (one_accuracy_test(k, constrain, sign, n, a, b, t))
	       ++ntests;
     }


     for (r = 0; r < impulse_rounds; ++r) {
	  if (r > n - r - 1)
	       continue;

	  caset(a, n, czero);
	  c_re(a[r]) = c_im(a[r]) = 1.0;

	  if (one_accuracy_test(k, constrain, sign, n, a, b, t))
	       ++ntests;
     }


     for (r = 0; r < impulse_rounds; ++r) {
	  if (r <= n - r - 1)
	       continue;

	  caset(a, n, czero);
	  c_re(a[n - r - 1]) = c_im(a[n - r - 1]) = 1.0;

	  if (one_accuracy_test(k, constrain, sign, n, a, b, t))
	       ++ntests;
     }


     for (r = 0; r < impulse_rounds; ++r) {
	  caset(a, n, czero);
	  i = rand() % n;
	  c_re(a[i]) = c_im(a[i]) = 1.0;

	  if (one_accuracy_test(k, constrain, sign, n, a, b, t))
	       ++ntests;
     }

     t[0] /= ntests;
     t[1] = sqrt(t[1] / ntests);
     t[3] /= ntests;
     t[4] = sqrt(t[4] / ntests);

     fftaccuracy_done();
}
