InsertPoint(int y, double x)
{
  size_t pos = 2*static_cast<size_t>(y - this->Extent[0]);
  double* &rhead = this->Raster[pos];
  double* &rtail = this->Raster[pos+1];


  size_t n = rtail - rhead;


  if (rhead == 0)
    {
    rhead = new double[2];
    rtail = rhead;
    }

  else if (n > 1 && (n & (n-1)) == 0)
    {
    double *ptr = new double[2*n];
    for (size_t i = 0; i < n; i++)
      {
      ptr[i] = rhead[i];
      }
    delete [] rhead;
    rhead = ptr;
    rtail = ptr + n;
    }


  *rtail++ = x;
}
