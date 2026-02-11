MaskToCavityRadius(R3Grid *mask, RNScalar min_cavity_radius)
{

  RNTime start_time;
  start_time.Read();


  R3Grid breadth_mask(*mask);


  for (int i = 0; i < breadth_mask.NEntries(); i++) {
    if (breadth_mask.GridValue(i) != 0) breadth_mask.SetGridValue(i, 1);
  }


  breadth_mask.Erode(min_cavity_radius);
  breadth_mask.Dilate(min_cavity_radius);


  mask->Mask(breadth_mask);


  if (print_verbose) {
    printf("Masked to cavity radius .. \n");
    printf("  Time = %.2f seconds\n", start_time.Elapsed());
    printf("  Min cavity radius = %g\n", min_cavity_radius);
    printf("  Cardinality = %d\n", mask->Cardinality());
    printf("  Volume = %g\n", mask->Volume());
    RNInterval grid_range = mask->Range();
    printf("  Minimum = %g\n", grid_range.Min());
    printf("  Maximum = %g\n", grid_range.Max());
    printf("  L1Norm = %g\n", mask->L1Norm());
    printf("  L2Norm = %g\n", mask->L2Norm());
    fflush(stdout);
  }
}
