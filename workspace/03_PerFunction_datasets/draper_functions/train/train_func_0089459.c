asn1PE_H245DialingInformationNetworkType (OOCTXT* pctxt, H245DialingInformationNetworkType* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;


   extbit = (ASN1BOOL)(pvalue->t > 3);

   encodeBit (pctxt, extbit);

   if (!extbit) {


      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return stat;


      switch (pvalue->t)
      {

         case 1:
            stat = asn1PE_H245NonStandardMessage (pctxt, pvalue->u.nonStandard);
            if (stat != ASN_OK) return stat;
            break;


         case 2:

            break;


         case 3:

            break;

         default:
            return ASN_E_INVOPT;
      }
   }
   else {


      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return stat;


      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) return freeContext (&lctxt), stat;

      switch (pvalue->t)
      {

         case 4:

            openType.data = encodeGetMsgPtr (&lctxt, (int*)&openType.numocts);
            break;

         default:
            ;
      }

      stat = encodeByteAlign (pctxt);
      if (stat != ASN_OK) return freeContext (&lctxt), stat;

      stat = encodeOpenType (pctxt, openType.numocts, openType.data);
      if (stat != ASN_OK) return freeContext (&lctxt), stat;

      freeContext (&lctxt);
   }

   return (stat);
}
