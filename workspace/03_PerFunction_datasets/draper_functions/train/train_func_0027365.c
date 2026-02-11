setup(bench_problem *p)
{
     double tim;

     if (amnesia) {
	  FFTW(forget_wisdom)();
	  havewisdom = 0;
     }


     FFTW(free(FFTW(malloc(42))));

     rdwisdom();
     install_hook();

#ifdef HAVE_SMP
     if (verbose > 1 && nthreads > 1) printf("NTHREADS = %d\n", nthreads);
#endif

     timer_start(USER_TIMER);
     the_plan = mkplan(p, preserve_input_flags(p) | the_flags);
     tim = timer_stop(USER_TIMER);
     if (verbose > 1) printf("planner time: %g s\n", tim);

     BENCH_ASSERT(the_plan);

     {
	  double add, mul, nfma, cost, pcost;
	  FFTW(flops)(the_plan, &add, &mul, &nfma);
	  cost = FFTW(estimate_cost)(the_plan);
	  pcost = FFTW(cost)(the_plan);
	  if (verbose > 1) {
	       FFTW(print_plan)(the_plan);
	       printf("\n");
	       printf("flops: %0.0f add, %0.0f mul, %0.0f fma\n",
		      add, mul, nfma);
	       printf("estimated cost: %f, pcost = %f\n", cost, pcost);
	  }
     }
}
