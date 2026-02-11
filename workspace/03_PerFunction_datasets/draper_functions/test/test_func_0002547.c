asn1PE_H245CloseLogicalChannel (OOCTXT* pctxt, H245CloseLogicalChannel* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;
   ASN1OpenType openType;
   OOCTXT lctxt;


   extbit = (ASN1BOOL)(pvalue->m.reasonPresent);

   encodeBit (pctxt, extbit);


   stat = asn1PE_H245LogicalChannelNumber (pctxt, pvalue->forwardLogicalChannelNumber);
   if (stat != ASN_OK) return stat;


   stat = asn1PE_H245CloseLogicalChannel_source (pctxt, &pvalue->source);
   if (stat != ASN_OK) return stat;

   if (extbit) {


      stat = encodeSmallNonNegWholeNumber (pctxt, 0);
      if (stat != ASN_OK) return stat;


      encodeBit (pctxt, (ASN1BOOL)pvalue->m.reasonPresent);


      if (pvalue->m.reasonPresent) {
         initContext (&lctxt);
         stat = setPERBuffer (&lctxt, 0, 0, TRUE);
         if (stat != ASN_OK) return freeContext (&lctxt), stat;

         stat = asn1PE_H245CloseLogicalChannel_reason (&lctxt, &pvalue->reason);
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
