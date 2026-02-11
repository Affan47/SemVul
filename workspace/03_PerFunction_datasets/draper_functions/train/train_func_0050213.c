GPS_Math_DegMinSec_To_Deg(int32 d, int32 m, double s, double* deg)
{

  *deg = ((double)abs(d)) + ((double)m + s / (double)60.0) / (double)60.0;
  if (d<0) {
    *deg = -*deg;
  }

  return;
}
