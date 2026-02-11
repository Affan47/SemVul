compute(vnl_vector<vcl_complex<double> > const &a)
{

  vnl_matrix<vcl_complex<double> > comp(N, N);
  comp.fill(0);
  for (unsigned i=0; i<N-1; ++i)
    comp(i+1, i) = 1;
  for (unsigned i=0; i<N; ++i)
    comp(i, N-1) = -a[N-1-i];


  solns = vnl_complex_eigensystem(comp,
                                  false,
                                  false).W;
#ifdef DEBUG
  vcl_cerr << "s = " << solns << '\n';
#endif
}
