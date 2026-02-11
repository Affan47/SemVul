asn1PE_H225ANSI_41_UIM_system_id (OOCTXT* pctxt, H225ANSI_41_UIM_system_id* pvalue)
{
   static Asn1SizeCnst sid_lsize1 = { 0, 1, 4, 0 };
   static Asn1SizeCnst mid_lsize1 = { 0, 1, 4, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = (ASN1BOOL)(pvalue->t > 2);

   encodeBit (pctxt, extbit);

   if (!extbit) {


      stat = encodeConsUnsigned (pctxt, pvalue->t - 1, 0, 1);
      if (stat != ASN_OK) return stat;


      switch (pvalue->t)
      {

         case 1:
            addSizeConstraint (pctxt, &sid_lsize1);

            stat = encodeConstrainedStringEx (pctxt, pvalue->u.sid, gs_H323_MESSAGES_ANSI_41_UIM_system_id_sid_CharSet, 4, 4, 7);
            if (stat != ASN_OK) return stat;
            break;


         case 2:
            addSizeConstraint (pctxt, &mid_lsize1);

            stat = encodeConstrainedStringEx (pctxt, pvalue->u.mid, gs_H323_MESSAGES_ANSI_41_UIM_system_id_mid_CharSet, 4, 4, 7);
            if (stat != ASN_OK) return stat;
            break;

         default:
            return ASN_E_INVOPT;
      }
   }
   else {


      stat = encodeSmallNonNegWholeNumber (pctxt, pvalue->t - 3);
      if (stat != ASN_OK) return stat;


   }

   return (stat);
}
