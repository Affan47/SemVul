asn1PE_H245IS11172VideoMode (OOCTXT* pctxt, H245IS11172VideoMode* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.videoBitRatePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.vbvBufferSizePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.samplesPerLinePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.linesPerFramePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.pictureRatePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.luminanceSampleRatePresent);


   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->constrainedBitstream);
   if (stat != ASN_OK) return stat;


   if (pvalue->m.videoBitRatePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->videoBitRate, 0U, 1073741823U);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.vbvBufferSizePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->vbvBufferSize, 0U, 262143U);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.samplesPerLinePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->samplesPerLine, 0U, 16383U);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.linesPerFramePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->linesPerFrame, 0U, 16383U);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.pictureRatePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->pictureRate, 0U, 15U);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.luminanceSampleRatePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->luminanceSampleRate, 0U, ASN1UINT_MAX);
      if (stat != ASN_OK) return stat;

   }

   return (stat);
}
