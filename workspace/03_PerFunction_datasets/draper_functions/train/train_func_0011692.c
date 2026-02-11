expressible_as_api_many(bench_tensor *t)
{
     int i;

     BENCH_ASSERT(FINITE_RNK(t->rnk));

     i = t->rnk - 1;
     while (--i >= 0) {
	  bench_iodim *d = t->dims + i;
	  if (d[0].is % d[1].is) return 0;
	  if (d[0].os % d[1].os) return 0;
     }
     return 1;
}
