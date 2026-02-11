gen_random_matrix(int dim1, int dim2) {

  const int random_range = 512;
  struct complex ** result;
  struct timeval seedtime;
  int seed;

  result = new_empty_matrix(dim1, dim2);


  gettimeofday(&seedtime, NULL);
  seed = seedtime.tv_usec;
  srandom(seed);


  for (int i = 0; (i < dim1); i++) {
    for (int j = 0; (j < dim2); j++) {

      result[i][j].real = (float)(random() % random_range);
      result[i][j].imag = (float)(random() % random_range);


      if (random() & 1) result[i][j].real = -result[i][j].real;
      if (random() & 1) result[i][j].imag = -result[i][j].imag;
    }
  }

  return result;
}
