addDataVIA(aName, aCut, aWidth, aHeight)
  char *aName;
  char  aCut;
  long  aWidth;
  long  aHeight;
{
  if (LV_mVIA > SIZE_TDATAVIA) {
    errMBK  ("DEFloadlophig");
    eprintf ("VIA table overfow (more than %d VIAs).\n", SIZE_TDATAVIA);
    EXIT (1);
  }

  tDataVIA[LV_mVIA].name   = namealloc (aName);
  tDataVIA[LV_mVIA].VIA    = aCut;
  tDataVIA[LV_mVIA].flags |= F_DATA_SET;
  tDataVIA[LV_mVIA].width  = aWidth;
  tDataVIA[LV_mVIA].height = aHeight;

  LV_mVIA++;
}
