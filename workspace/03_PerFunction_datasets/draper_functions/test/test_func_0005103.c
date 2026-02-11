Sinc(const double x) {
    if (fabs(x)<1e-9) {
      return 1-x*x*M_PI*M_PI/6.0;
    } else {
      return sin(M_PI*x)/(M_PI*x);
    }
  }
