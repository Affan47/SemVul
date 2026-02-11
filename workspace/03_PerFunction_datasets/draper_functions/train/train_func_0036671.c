get_JtJ()
{
  if (!set_covariance_)
  {
    vcl_cerr << __FILE__ ": get_covariance() not confirmed tested  yet\n";
    unsigned int n = fdjac_.rows();


    vnl_matrix<double> r = fdjac_.extract(n,n).transpose();


    for (unsigned int i=0; i<n; ++i)
      for (unsigned int j=0; j<i; ++j)
        r(i,j) = 0.0;


    vnl_matrix<double> rtr;
    vnl_fastops::AtA(rtr, r);
    vnl_matrix<double> rtrpt (n, n);


    vnl_vector<int> jpvt(n);
    for (unsigned int j = 0; j < n; ++j) {
      unsigned int i = 0;
      for (; i < n; i++) {
        if (ipvt_[i] == (int)j+1) {
          jpvt (j) = i;
          break;
        }
      }
      rtrpt.set_column(j, rtr.get_column(i));
    }


    for (unsigned int j = 0; j < n; ++j) {
      inv_covar_.set_row (j, rtrpt.get_row (jpvt(j)));
    }

    set_covariance_ = true;
  }
  return inv_covar_;
}
