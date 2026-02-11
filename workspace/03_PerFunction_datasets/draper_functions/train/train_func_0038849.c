vnl_solve_qp_non_neg_step(const vnl_matrix<double>& H,
                               const vnl_vector<double>& g,
                               const vnl_matrix<double>& A,
                               const vnl_vector<double>& b,
                               vnl_vector<double>& x,
                               std::vector<bool>& valid,
                               unsigned& n_valid)
{


  unsigned n=H.rows();
  unsigned nc=A.rows();

  vnl_matrix<double> H1(n_valid,n_valid);
  vnl_matrix<double> A1(nc,n_valid);
  unsigned j1=0;
  for (unsigned j=0;j<n;++j)
  {
    if (valid[j])
    {


      unsigned i1=0;
      for (unsigned i=0;i<n;++i)
      {
        if (valid[i]) { H1(i1,j1)=H(i,j); ++i1; }
      }


      for (unsigned i=0;i<nc;++i,++i1) A1(i,j1)=A(i,j);

      ++j1;
    }
  }

  vnl_vector<double> x1(n_valid);
  vnl_vector<double> g1(n_valid);
  unsigned i1=0;
  for (unsigned i=0;i<n;++i)
  {
    if (valid[i]) { g1[i1]=g[i]; x1[i1]=x[i]; ++i1; }
  }
  g1 += H1*x1;

  vnl_vector<double> b1(b);
  b1-= A1*x1;

  vnl_vector<double> dx(n_valid,0.0);

  vnl_solve_qp_with_equality_constraints(H1,g1,A1,b1,dx);


  return vnl_solve_qp_update_x(x,x1,dx,valid,n_valid);
}
