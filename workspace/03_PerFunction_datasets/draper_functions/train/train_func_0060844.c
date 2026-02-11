xfxphoton(double x, double Q) {
    vector<double> r(13);
    double mphoton;
    fevolvepdfphoton(&x, &Q, &r[0], &mphoton );
    r.push_back(mphoton);
    return r;
  }
