main(int argc, char **argv) {
  int i;
  int histargs = 0;

#ifdef DIMENSION
  if(argc != 1 && argc != 2 + global_dim) {
    printf("Usage: %s [histogram]\n", argv[0]);
    printf("Dimension: %d\n", global_dim);
    return 1;
  }
  if(argc == 2 + global_dim)
    histargs = 1;
#else
  if(argc < 2) {
    printf("Usage: %s dimensions [histogram]\n", argv[0]);
    return 1;
  }
  sscanf(argv[1], "%d", &global_dim);
  if(argc != 2 && argc != 3 + global_dim) {
    printf("Usage: %s dimensions [histogram]\n", argv[0]);
    return 1;
  }
  if(argc == 3 + global_dim)
    histargs = 2;
  ncells = 1 << global_dim;
#endif
  global_start_time = currentTime();

  arrangeDims();
  initCache();
  initPermutations();

  if(histargs) {
    for(i = 0; i <= global_dim; i++)
      histogram[i] = atoi(argv[i + histargs]);
    buildHistograms(global_dim, 1);
    return 0;
  }
  histogram[0] = 1;
  for(i = 1; i <= global_dim; i++)
    histogram[i] = 0;

  buildHistograms(0, 0);
  buildHistograms(0, 1);
  fprintf(stderr, "Rotations checked: %d\n", nrotationsChecked);

  return 0;
}
