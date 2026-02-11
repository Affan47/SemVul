adapt_method_stat(MESH *mesh, ADAPT_STAT *adapt)
{
  FUNCNAME("adapt_method_stat");
  int      iter;
  REAL     est;
  clock_t  first;

  TEST_EXIT(mesh, "no MESH\n");
  TEST_EXIT(adapt, "no ADAPT_STAT\n");


  if (adapt->build_before_refine)  adapt->build_before_refine(mesh, 0);
  if (adapt->build_before_coarsen) adapt->build_before_coarsen(mesh, 0);
  if (adapt->build_after_coarsen)  adapt->build_after_coarsen(mesh, 0);
  if (adapt->solve)
  {
    first = clock();
    adapt->solve(mesh);
    INFO(adapt->info,8,"solution of discrete system needed %.5lg seconds\n",
			TIME_USED(first,clock()));
  }

  first = clock();
  est = adapt->estimate ? adapt->estimate(mesh, adapt) : 0.0;
  INFO(adapt->info,8,"estimation of the error needed %.5lg seconds\n",
		      TIME_USED(first,clock()));

  for (iter = 0;
       (est > adapt->tolerance) &&
	 ((adapt->max_iteration <= 0) || (iter < adapt->max_iteration));
       iter++)
  {
    if (adapt_mesh(mesh, adapt))
    {
      if (adapt->solve)
      {
	first = clock();
	adapt->solve(mesh);
	INFO(adapt->info,8,
	  "solution of discrete system needed %.5lg seconds\n",
	   TIME_USED(first,clock()));
      }
      first = clock();
      est = adapt->estimate ? adapt->estimate(mesh, adapt) : 0.0;
      INFO(adapt->info,8,"estimation of the error needed %.5lg seconds\n",
			  TIME_USED(first,clock()));
    }
    else
    {
      ERROR("no mesh adaption, but estimate above tolerance ???\n");
      break;
    }
    INFO(adapt->info, 4,"iter: %d", iter);
    PRINT_INFO(adapt->info, 4,", tol = %.4le", adapt->tolerance);
    PRINT_INFO(adapt->info, 4,", estimate = %.4le\n", est);
  }

  if (est > adapt->tolerance)
  {
    MSG("max_iterations REACHED: %d\n", adapt->max_iteration);
    MSG("prescribed tolerance    %le\n", adapt->tolerance);
    MSG("finished with estimate  %le\n", est);
  }
  else
  {
    INFO(adapt->info, 2,"no of iterations:       %d\n", iter);
    INFO(adapt->info, 2,"prescribed tolerance    %.4le\n", adapt->tolerance);
    INFO(adapt->info, 2,"finished with estimate  %.4le\n", est);
  }
  return;
}
