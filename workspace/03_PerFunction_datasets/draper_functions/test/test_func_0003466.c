asn1PE_H225CircuitIdentifier (OOCTXT* pctxt, H225CircuitIdentifier* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;


   extbit = (ASN1BOOL)(pvalue->m.carrierPresent);

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.cicPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.groupPresent);


   if (pvalue->m.cicPresent) {
      stat = asn1PE_H225CicInfo (pctxt, &pvalue->cic);
      if (stat != ASN_OK) return stat;
   }


   if (pvalue->m.groupPresent) {
      stat = asn1PE_H225GroupID (pctxt, &pvalue->group);
      if (stat != ASN_OK) return stat;
   }

   if (extbit) {


      stat = encodeSmallNonNegWholeNumber (pctxt, 0);
      if (stat != ASN_OK) return stat;


      encodeBit (pctxt, (ASN1BOOL)pvalue->m.carrierPresent);


      if (pvalue->m.carrierPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         stat = asn1PE_H225CarrierInfo (&lctxt, &pvalue->carrier);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         stat = encodeByteAlign (&lctxt);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);

         stat = encodeOpenType (pctxt, openType.numocts, openType.data);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         freeContext (&lctxt);
      }

   }

   return (stat);
}
