vnl_discrete_diff_fwd(vnl_least_squares_function *lsf,
                           vnl_vector<double> const &h,
                           vnl_vector<double> const &x,
                           vnl_vector<double> const &y,
                           vnl_matrix<double>       &J)
{
  unsigned m=J.rows();
  unsigned n=J.columns();
  assert(m==lsf->get_number_of_residuals());
  assert(m==y.size());
  assert(n==lsf->get_number_of_unknowns());
  assert(n==h.size());
  assert(n==x.size());

  vnl_vector<double> tx(n);
  vnl_vector<double> ty(m);

  for (unsigned j=0;j<n;j++) {
    tx=x; tx(j) += h(j);
    lsf->f(tx,ty);
    if (lsf->failure)
      return false;
    for (unsigned i=0;i<m;i++)
      J(i,j) = (ty(i)-y(i))/h(j);
  }
  return true;
}
