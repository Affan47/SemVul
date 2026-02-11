xt_m_inv_x(const vnl_vector<double>& x) const
{
  unsigned n=d_.size();
  assert(x.size()==n);
  vnl_vector<double> y=x;

  double sum = y[0]*y[0]/d_[0];
  for (unsigned i=1;i<n;++i)
  {
    y[i] -= dot(L_[i],y.data_block(),i);
    sum += y[i]*y[i]/d_[i];
  }
  return sum;
}
