coin_init_random_vec(double *work, int n)
{
  double deseed = 12345678.0;

  for (int i = 0; i < n; ++i) {
    deseed *= 16807.;
    int jseed = static_cast<int> (deseed /    DSEED2);
    deseed -= static_cast<double> (jseed) * DSEED2;
    double random = deseed /  DSEED2;

    work[i]=random;
  }
}
