getMaxDim() const
{
  int maxDim = 0;
  real d = hi[0]-lo[0];
  for(int j=1; j<3; j++) {
    real x = hi[j] - lo[j];
    if(x>d) {
      d = x;
      maxDim = j;
    }
  }
  return maxDim;
}
