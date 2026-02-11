asn1PE_H225StimulusControl (OOCTXT* pctxt, H225StimulusControl* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.isTextPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.h248MessagePresent);


   if (pvalue->m.nonStandardPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandard);
      if (stat != ASN_OK) return stat;
   }


   if (pvalue->m.isTextPresent) {

   }


   if (pvalue->m.h248MessagePresent) {
      stat = encodeOctetString (pctxt, pvalue->h248Message.numocts, pvalue->h248Message.data);
      if (stat != ASN_OK) return stat;
   }

   return (stat);
}
