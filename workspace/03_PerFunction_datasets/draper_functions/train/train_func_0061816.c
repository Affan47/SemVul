asn1PE_H245VCCapability_availableBitRates_type (OOCTXT* pctxt, H245VCCapability_availableBitRates_type* pvalue)
{
   int stat = ASN_OK;


   stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
   if (stat != ASN_OK) return stat;


   switch (pvalue->t)
   {

      case 1:
         stat = encodeConsUnsigned (pctxt, pvalue->u.singleBitRate, 1U, 65535U);
         if (stat != ASN_OK) return stat;

         break;


      case 2:
         stat = asn1PE_H245VCCapability_availableBitRates_type_rangeOfBitRates (pctxt, pvalue->u.rangeOfBitRates);
         if (stat != ASN_OK) return stat;
         break;

      default:
         return ASN_E_INVOPT;
   }

   return (stat);
}
