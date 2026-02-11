compute(vnl_vector<double> const& x, double *val, vnl_vector<double>* g)
{
  if (val) *val = this->f(x);
  if (g) this->gradf(x, *g);
}
