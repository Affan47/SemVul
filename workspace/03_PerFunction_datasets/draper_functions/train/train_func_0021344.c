mgdevice_NULL(void)
{
  if (MGC != NULL && MGC->devno != MGD_NULL)
    MGC = NULL;
  _mgf = mgnullfuncs;
  return 1;
}
