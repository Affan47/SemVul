asn1PE_H245H223Capability_h223MultiplexTableCapability_enhanced (OOCTXT* pctxt, H245H223Capability_h223MultiplexTableCapability_enhanced* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);


   stat = encodeConsUnsigned (pctxt, pvalue->maximumNestingDepth, 1U, 15U);
   if (stat != ASN_OK) return stat;


   stat = encodeConsUnsigned (pctxt, pvalue->maximumElementListSize, 2U, 255U);
   if (stat != ASN_OK) return stat;


   stat = encodeConsUnsigned (pctxt, pvalue->maximumSubElementListSize, 2U, 255U);
   if (stat != ASN_OK) return stat;

   return (stat);
}
