Blur(R3Grid *grid, RNScalar sigma)
{

  if (sigma == 0) return;


  RNTime start_time;
  start_time.Read();


  grid->Blur(sigma * grid->WorldToGridScaleFactor());


  if (print_verbose) {
    printf("Blurred grid .. \n");
    printf("  Time = %.2f seconds\n", start_time.Elapsed());
    printf("  Sigma = %g\n", sigma);
    printf("  Cardinality = %d\n", grid->Cardinality());
    printf("  Volume = %g\n", grid->Volume());
    RNInterval grid_range = grid->Range();
    printf("  Minimum = %g\n", grid_range.Min());
    printf("  Maximum = %g\n", grid_range.Max());
    printf("  L1Norm = %g\n", grid->L1Norm());
    printf("  L2Norm = %g\n", grid->L2Norm());
    fflush(stdout);
  }
}
