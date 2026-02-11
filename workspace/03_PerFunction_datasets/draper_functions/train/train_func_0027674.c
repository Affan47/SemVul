cov(const Matrix& mat, const int norm)
{
  SymmetricMatrix res;
  Matrix tmp;
  int N;
  tmp=remmean(mat);
  if (norm == 1) {N = mat.Nrows();}
  else {N = mat.Nrows()-1;}
  res << tmp.t()*tmp;
  res = res/N;

  res.Release();
  return res;
}
