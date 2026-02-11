BitsEntropy(const int* const array, int n) {
  double retval = 0.;
  int sum = 0;
  int nonzeros = 0;
  int max_val = 0;
  int i;
  double mix;
  for (i = 0; i < n; ++i) {
    if (array[i] != 0) {
      sum += array[i];
      ++nonzeros;
      retval -= VP8LFastSLog2(array[i]);
      if (max_val < array[i]) {
        max_val = array[i];
      }
    }
  }
  retval += VP8LFastSLog2(sum);

  if (nonzeros < 5) {
    if (nonzeros <= 1) {
      return 0;
    }


    if (nonzeros == 2) {
      return 0.99 * sum + 0.01 * retval;
    }


    if (nonzeros == 3) {
      mix = 0.95;
    } else {
      mix = 0.7;
    }
  } else {
    mix = 0.627;
  }

  {
    double min_limit = 2 * sum - max_val;
    min_limit = mix * min_limit + (1.0 - mix) * retval;
    return (retval < min_limit) ? min_limit : retval;
  }
}
