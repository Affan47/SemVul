set_temperature(double *args)
{
  float temp=(float)args[0];
  if(0!=SLM_SetMMATemperature(&temp)){
    e("set mma temperature");
    return MYNAN;
  }
  return 1.0*temp;
}
