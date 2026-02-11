btAb(const vnl_matrix<double>& A, const vnl_vector<double>& b)
{
  const unsigned int m = A.rows();
  const unsigned int n = A.cols();
  const unsigned int l = b.size();


  if (m != l ) {
    std::cerr << "vnl_fastops::btAb: argument sizes do not match: " << m << " != " << l << '\n';
    std::abort();
  }
  if ( m != n ) {
    std::cerr << "vnl_fastops::btAb: not a square matrix: " << m << " != " << n << '\n';
    std::abort();
  }


  double const* const* a = A.data_array();
  double const* bb = b.data_block();

  double accum = 0;
  for (unsigned int i = 0; i < n; ++i)
    for (unsigned int j = 0; j < n; ++j) {
      accum += bb[j] * a[i][j] * bb[i];
    }
  return accum;
}
