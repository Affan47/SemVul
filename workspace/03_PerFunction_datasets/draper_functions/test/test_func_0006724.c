asn1PE_H245RSVPParameters (OOCTXT* pctxt, H245RSVPParameters* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.qosModePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokenRatePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.bucketSizePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.peakRatePresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.minPolicedPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.maxPktSizePresent);


   if (pvalue->m.qosModePresent) {
      stat = asn1PE_H245QOSMode (pctxt, &pvalue->qosMode);
      if (stat != ASN_OK) return stat;
   }


   if (pvalue->m.tokenRatePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->tokenRate, 1U, ASN1UINT_MAX);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.bucketSizePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->bucketSize, 1U, ASN1UINT_MAX);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.peakRatePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->peakRate, 1U, ASN1UINT_MAX);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.minPolicedPresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->minPoliced, 1U, ASN1UINT_MAX);
      if (stat != ASN_OK) return stat;

   }


   if (pvalue->m.maxPktSizePresent) {
      stat = encodeConsUnsigned (pctxt, pvalue->maxPktSize, 1U, ASN1UINT_MAX);
      if (stat != ASN_OK) return stat;

   }

   return (stat);
}
