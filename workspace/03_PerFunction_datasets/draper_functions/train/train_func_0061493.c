asn1PE_H245ParameterIdentifier (OOCTXT* pctxt, H245ParameterIdentifier* pvalue)
{
   static Asn1SizeCnst domainBased_lsize1 = { 0, 1, 64, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = (ASN1BOOL)(pvalue->t > 4);

   encodeBit (pctxt, extbit);

   if (!extbit) {


      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 3);
      if (stat != ASN_OK) return stat;


      switch (pvalue->t)
      {

         case 1:
            stat = encodeConsUnsigned (pctxt, pvalue->u.standard, 0U, 127U);
            if (stat != ASN_OK) return stat;

            break;


         case 2:
            stat = asn1PE_H245NonStandardParameter (pctxt, pvalue->u.h221NonStandard);
            if (stat != ASN_OK) return stat;
            break;


         case 3:
            stat = asn1PE_H245ParameterIdentifier_uuid (pctxt, pvalue->u.uuid);
            if (stat != ASN_OK) return stat;
            break;


         case 4:
            addSizeConstraint (pctxt, &domainBased_lsize1);

            stat = encodeConstrainedStringEx (pctxt, pvalue->u.domainBased, 0, 8, 7, 7);
            if (stat != ASN_OK) return stat;
            break;

         default:
            return ASN_E_INVOPT;
      }
   }
   else {


      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 5);
      if (stat != ASN_OK) return stat;


   }

   return (stat);
}
