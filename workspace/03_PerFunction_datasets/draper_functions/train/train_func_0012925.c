start(double*ignore)
{
  (void)ignore;
  if(0!=SLM_SetStartMMA()){
    e("start");
    return MYNAN;
  }
  return 0.0;
}
