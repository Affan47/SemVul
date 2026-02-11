_SetScalarGamma (SANE_Int * aiGamma, SANE_Int sfGamma)
{
  int j;
  double fGamma;
  fGamma = SANE_UNFIX (sfGamma);
  for (j = 0; j < SANE_GAMMA_SIZE; j++)
    {
      int iData;
      iData =
        floor (256.0 *
               pow (((double) j / (double) SANE_GAMMA_SIZE), 1.0 / fGamma));
      if (iData > 255)
        iData = 255;
      aiGamma[j] = iData;
    }
}
