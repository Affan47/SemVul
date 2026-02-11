initr(vcl_vector<unsigned int> const& ideg,
                  vcl_vector<vnl_rnpoly_solve_cmplx> const& p,
                  vcl_vector<vnl_rnpoly_solve_cmplx> const& q,
                  vcl_vector<vnl_rnpoly_solve_cmplx>& r,
                  vcl_vector<vnl_rnpoly_solve_cmplx>& pdg,
                  vcl_vector<vnl_rnpoly_solve_cmplx>& qdg)
{
  assert(ideg.size()==dim_);
  assert(p.size()==dim_);
  assert(q.size()==dim_);
  pdg.resize(dim_); qdg.resize(dim_); r.resize(dim_);
  for (unsigned int j=0;j<dim_;j++)
  {
    pdg[j] = powr(ideg[j],p[j]);
    qdg[j] = powr(ideg[j],q[j]);
    r[j] = q[j] / p[j];
  }
}
