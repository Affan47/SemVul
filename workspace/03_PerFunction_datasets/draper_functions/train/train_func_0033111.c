primitive() const
{
  int d = coeffs_.size();
  vnl_vector<double> cd (d+1);
  cd[d] = 0.0;
  for (int i=d-1,di=1; i>=0; --i,++di)
    cd[i] = coeffs_[i] / di;
  return vnl_real_polynomial(cd);
}
