sqrt(const Matrix& mat)
{
  Matrix res = mat;
  bool neg_flag = false;
  for (int mc=1; mc<=mat.Ncols(); mc++) {
    for (int mr=1; mr<=mat.Nrows(); mr++) {
      if(res(mr,mc)<0){ neg_flag = true; }
      res(mr,mc)=std::sqrt(std::abs(res(mr,mc)));
    }
  }
  if(neg_flag){


  }
  res.Release();
  return res;
}
