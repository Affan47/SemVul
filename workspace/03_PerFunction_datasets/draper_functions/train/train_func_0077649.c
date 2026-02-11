asn1PE_H245MaintenanceLoopRequest_type (OOCTXT* pctxt, H245MaintenanceLoopRequest_type* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = (ASN1BOOL)(pvalue->t > 3);

   encodeBit (pctxt, extbit);

   if (!extbit) {


      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 2);
      if (stat != ASN_OK) return stat;


      switch (pvalue->t)
      {

         case 1:

            break;


         case 2:
            stat = asn1PE_H245LogicalChannelNumber (pctxt, pvalue->u.mediaLoop);
            if (stat != ASN_OK) return stat;
            break;


         case 3:
            stat = asn1PE_H245LogicalChannelNumber (pctxt, pvalue->u.logicalChannelLoop);
            if (stat != ASN_OK) return stat;
            break;

         default:
            return ASN_E_INVOPT;
      }
   }
   else {


      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 4);
      if (stat != ASN_OK) return stat;


   }

   return (stat);
}
