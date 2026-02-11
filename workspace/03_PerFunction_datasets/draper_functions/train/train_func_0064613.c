asn1PE_H245OpenLogicalChannelAck_reverseLogicalChannelParameters_multiplexParameters (OOCTXT* pctxt, H245OpenLogicalChannelAck_reverseLogicalChannelParameters_multiplexParameters* pvalue)
{
   int stat = ASN_OK;
   OOCTXT lctxt;
   ASN1OpenType openType;
   ASN1BOOL extbit;


   extbit = (ASN1BOOL)(pvalue->t > 1);

   encodeBit (pctxt, extbit);

   if (!extbit) {


      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 0);
      if (stat != ASN_OK) return stat;


      switch (pvalue->t)
      {

         case 1:
            stat = asn1PE_H245H222LogicalChannelParameters (pctxt, pvalue->u.h222LogicalChannelParameters);
            if (stat != ASN_OK) return stat;
            break;

         default:
            return ASN_E_INVOPT;
      }
   }
   else {


      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 2);
      if (stat != ASN_OK) return stat;


      initContext (&lctxt);
      stat = setPERBuffer (&lctxt, 0, 0, TRUE);
      if (stat != ASN_OK) return freeContext (&lctxt), stat;

      switch (pvalue->t)
      {

         case 2:
            stat = asn1PE_H245H2250LogicalChannelParameters (&lctxt, pvalue->u.h2250LogicalChannelParameters);
            if (stat != ASN_OK) return freeContext (&lctxt), stat;
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
