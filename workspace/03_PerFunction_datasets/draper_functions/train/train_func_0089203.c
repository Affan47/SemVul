asn1PE_H225TunnelledProtocolAlternateIdentifier (OOCTXT* pctxt, H225TunnelledProtocolAlternateIdentifier* pvalue)
{
   static Asn1SizeCnst protocolType_lsize1 = { 0, 1, 64, 0 };
   static Asn1SizeCnst protocolVariant_lsize1 = { 0, 1, 64, 0 };
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.protocolVariantPresent);


   addSizeConstraint (pctxt, &protocolType_lsize1);

   stat = encodeConstrainedStringEx (pctxt, pvalue->protocolType, 0, 8, 7, 7);
   if (stat != ASN_OK) return stat;


   if (pvalue->m.protocolVariantPresent) {
      addSizeConstraint (pctxt, &protocolVariant_lsize1);

      stat = encodeConstrainedStringEx (pctxt, pvalue->protocolVariant, 0, 8, 7, 7);
      if (stat != ASN_OK) return stat;
   }

   return (stat);
}
