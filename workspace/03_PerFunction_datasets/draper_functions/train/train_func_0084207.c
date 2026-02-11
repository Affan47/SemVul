asn1PE_H245RTPH263VideoRedundancyEncoding (OOCTXT* pctxt, H245RTPH263VideoRedundancyEncoding* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.containedThreadsPresent);


   stat = encodeConsUnsigned (pctxt, pvalue->numberOfThreads, 1U, 16U);
   if (stat != ASN_OK) return stat;


   stat = encodeConsUnsigned (pctxt, pvalue->framesBetweenSyncPoints, 1U, 256U);
   if (stat != ASN_OK) return stat;


   stat = asn1PE_H245RTPH263VideoRedundancyEncoding_frameToThreadMapping (pctxt, &pvalue->frameToThreadMapping);
   if (stat != ASN_OK) return stat;


   if (pvalue->m.containedThreadsPresent) {
      stat = asn1PE_H245RTPH263VideoRedundancyEncoding_containedThreads (pctxt, &pvalue->containedThreads);
      if (stat != ASN_OK) return stat;
   }

   return (stat);
}
