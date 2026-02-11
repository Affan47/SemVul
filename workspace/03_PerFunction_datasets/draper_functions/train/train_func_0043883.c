quantile(const Matrix& in, int which)
{
  int num = in.Ncols();
  Matrix res(1,num);
  for (int ctr=1; ctr<=num; ctr++){
    ColumnVector tmp = in.Column(ctr);
    res(1,ctr) = quantile(tmp,which);
  }
  res.Release();
  return res;
}
