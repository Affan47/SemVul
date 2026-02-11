predict(std::vector<unsigned int> const& ideg,
                    std::vector<vnl_rnpoly_solve_cmplx> const& pdg,
                    std::vector<vnl_rnpoly_solve_cmplx> const& qdg,
                    double step, double& t,
                    std::vector<vnl_rnpoly_solve_cmplx>& x,
                    std::vector<int> const& polyn,
                    std::vector<double> const& coeff,
                    std::vector<unsigned int> const& terms)
{
  assert(ideg.size()==dim_);
  assert(terms.size()==dim_);
  assert(x.size()==dim_);

  double maxdt =.2;


  std::vector<vnl_rnpoly_solve_cmplx> dht(dim_),dhx(dim_*dim_),dz(dim_),h(dim_),rhs(dim_);

  hfunr(ideg,pdg,qdg,t,x,h,dhx,dht,polyn,coeff,terms);

  for (unsigned int j=0; j<dim_; ++j)
    rhs[j] = - dht[j];


  if (linnr(dhx,rhs,dz) == 1) return;


  double factor = step/(1+xnorm(dz));
  if (factor>maxdt) factor = maxdt;

  bool tis1=true;
  if (t+factor>1) { tis1 = false; factor = 1.0 - t; }


  for (unsigned int j=0; j<dim_; ++j)
    x[j] += dz[j] * factor;

  if (tis1) t += factor;
  else      t = 1.0;
}
