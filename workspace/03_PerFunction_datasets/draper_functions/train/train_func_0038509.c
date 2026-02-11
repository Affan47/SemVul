Average(float *Data, int Len)
{ double Sum; int i;
  for(Sum=0.0,i=0; i<Len; i++) Sum+=Data[i];
  return Sum/Len; }
