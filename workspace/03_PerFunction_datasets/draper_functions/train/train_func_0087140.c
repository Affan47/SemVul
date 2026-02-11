asn1PE_H245ParameterValue (OOCTXT* pctxt, H245ParameterValue* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = (ASN1BOOL)(pvalue->t > 8);

   encodeBit (pctxt, extbit);

   if (!extbit) {


      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 7);
      if (stat != ASN_OK) return stat;


      switch (pvalue->t)
      {

         case 1:

            break;


         case 2:
            stat = encodeConsUnsigned (pctxt, pvalue->u.booleanArray, 0U, 255U);
            if (stat != ASN_OK) return stat;

            break;


         case 3:
            stat = encodeConsUnsigned (pctxt, pvalue->u.unsignedMin, 0U, 65535U);
            if (stat != ASN_OK) return stat;

            break;


         case 4:
            stat = encodeConsUnsigned (pctxt, pvalue->u.unsignedMax, 0U, 65535U);
            if (stat != ASN_OK) return stat;

            break;


         case 5:
            stat = encodeConsUnsigned (pctxt, pvalue->u.unsigned32Min, 0U, ASN1UINT_MAX);
            if (stat != ASN_OK) return stat;

            break;


         case 6:
            stat = encodeConsUnsigned (pctxt, pvalue->u.unsigned32Max, 0U, ASN1UINT_MAX);
            if (stat != ASN_OK) return stat;

            break;


         case 7:
            stat = encodeOctetString (pctxt, pvalue->u.octetString->numocts, pvalue->u.octetString->data);
            if (stat != ASN_OK) return stat;
            break;


         case 8:
            stat = asn1PE_H245_SeqOfH245GenericParameter (pctxt, (H245_SeqOfH245GenericParameter*)pvalue->u.genericParameter);
            if (stat != ASN_OK) return stat;
            break;

         default:
            return ASN_E_INVOPT;
      }
   }
   else {


      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 9);
      if (stat != ASN_OK) return stat;


   }

   return (stat);
}
