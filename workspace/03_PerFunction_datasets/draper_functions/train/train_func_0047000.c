test_planner(int rank)
{


     int i, dim;
     int r, s;
     fftw_plan p[PLANNER_TEST_SIZE];
     fftwnd_plan pnd[PLANNER_TEST_SIZE];
     int *narr, maxdim;

     chk_mem_leak = 0;
     verbose--;

     please_wait();
     if (rank < 1)
	  rank = 1;

     narr = (int *) fftw_malloc(rank * sizeof(int));

     maxdim = (int) pow(8192.0, 1.0/rank);

     for (i = 0; i < PLANNER_TEST_SIZE; ++i) {
	  p[i] = (fftw_plan) 0;
	  pnd[i] = (fftwnd_plan) 0;
     }

     for (i = 0; i < PLANNER_TEST_SIZE * PLANNER_TEST_SIZE; ++i) {
	  r = rand();
	  if (r < 0)
	       r = -r;
	  r = r % PLANNER_TEST_SIZE;

	  for (dim = 0; dim < rank; ++dim) {
	       do {
		    s = rand();
		    if (s < 0)
			 s = -s;
		    s = s % maxdim + 1;
	       } while (s == 0);
	       narr[dim] = s;
	  }

	  if (rank == 1) {
	       if (p[r])
		    rfftw_destroy_plan(p[r]);

	       p[r] = rfftw_create_plan(narr[0], random_dir(), measure_flag |
					wisdom_flag);
	       if (paranoid && narr[0] < 200)
		    test_correctness(narr[0]);
	  }
	  if (pnd[r])
	       rfftwnd_destroy_plan(pnd[r]);

	  pnd[r] = rfftwnd_create_plan(rank, narr,
				       random_dir(), measure_flag |
				       wisdom_flag);

	  if (i % (PLANNER_TEST_SIZE * PLANNER_TEST_SIZE / 20) == 0) {
	       WHEN_VERBOSE(0, printf("test planner: so far so good\n"));
	       WHEN_VERBOSE(0, printf("test planner: iteration %d out of %d\n",
			      i, PLANNER_TEST_SIZE * PLANNER_TEST_SIZE));
	  }
     }

     for (i = 0; i < PLANNER_TEST_SIZE; ++i) {
	  if (p[i])
	       rfftw_destroy_plan(p[i]);
	  if (pnd[i])
	       rfftwnd_destroy_plan(pnd[i]);
     }

     fftw_free(narr);
     verbose++;
     chk_mem_leak = 1;
}
