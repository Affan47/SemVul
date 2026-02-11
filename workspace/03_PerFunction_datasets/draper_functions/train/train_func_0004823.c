get_rms_error(vnl_vector<double> const& x) const
{
  vnl_vector<double> resid(n_);
  vnl_vector<double> b(n_);

  multiply(x, resid);
  get_rhs(b);

  resid -= b;

  return resid.rms();
}
