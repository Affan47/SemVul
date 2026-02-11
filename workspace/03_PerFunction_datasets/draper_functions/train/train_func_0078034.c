amdmsCheckFitValues(amdmsDATA *fitValues, int nValues, int iPixel)
{
  int    iValue;

  for (iValue = 0; iValue < nValues; iValue++) {
    if (isnan(fitValues[iValue].data[iPixel])) {
      amdmsWarning(__FILE__, __LINE__, "fit value %d of pixel %d is NAN", iValue, iPixel);
    }
    if (isinf(fitValues[iValue].data[iPixel])) {
      amdmsWarning(__FILE__, __LINE__, "fit value %d of pixel %d is INF", iValue, iPixel);
    }
  }
}
