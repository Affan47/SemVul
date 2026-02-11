unifrnd(const int dim1, const int dim2, const float start, const float end)
{
  int tdim = dim2;
  double tmpD=1.0;
  if(tdim<0){tdim=dim1;}
  Matrix res(dim1,tdim);
  for (int mc=1; mc<=res.Ncols(); mc++) {
    for (int mr=1; mr<=res.Nrows(); mr++) {
      tmpD = (rand()+1)/double(RAND_MAX+2.0);
      res(mr,mc)=(tmpD)*(end-start)+start;


    }
  }

  res.Release();
  return res;
}
