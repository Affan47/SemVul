HPCC_LocalVectorSize(HPCC_Params *params, int vecCnt, size_t size, int pow2) {
  int flg2, maxIntBits2;


  maxIntBits2 = sizeof(int) * 8 - 2;


  for (flg2 = 1; params->HPLMaxProcMem / size / vecCnt >> flg2; ++flg2)
    ;
  --flg2;

  if (flg2 <= maxIntBits2) {
    if (pow2)
      return 1 << flg2;

    return params->HPLMaxProcMem / size / vecCnt;
  }

  return 1 << maxIntBits2;
}
