mct_decode_custom(

             OPJ_BYTE * pDecodingData,

             OPJ_UINT32 n,

             OPJ_BYTE ** pData,

             OPJ_UINT32 pNbComp,

             OPJ_UINT32 isSigned)
{
  OPJ_FLOAT32 * lMct;
  OPJ_UINT32 i;
  OPJ_UINT32 j;
  OPJ_UINT32 k;

  OPJ_FLOAT32 * lCurrentData = 00;
  OPJ_FLOAT32 * lCurrentResult = 00;
  OPJ_FLOAT32 ** lData = (OPJ_FLOAT32 **) pData;

  lCurrentData = (OPJ_FLOAT32 *) opj_malloc (2 * pNbComp * sizeof(OPJ_FLOAT32));
  if
    (! lCurrentData)
  {
    return false;
  }
  lCurrentResult = lCurrentData + pNbComp;

  for
    (i = 0; i < n; ++i)
  {
    lMct = (OPJ_FLOAT32 *) pDecodingData;
    for
      (j=0;j<pNbComp;++j)
    {
      lCurrentData[j] = (OPJ_FLOAT32) (*(lData[j]));
    }
    for
      (j=0;j<pNbComp;++j)
    {
      lCurrentResult[j] = 0;
      for
        (k=0;k<pNbComp;++k)
      {
        lCurrentResult[j] += *(lMct++) * lCurrentData[k];
      }
      *(lData[j]++) = (OPJ_FLOAT32) (lCurrentResult[j]);
    }
  }
  opj_free(lCurrentData);
  return true;
}
