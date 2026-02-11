asn1PE_H225InfoRequestNak (OOCTXT* pctxt, H225InfoRequestNak* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.nonStandardDataPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.altGKInfoPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.tokensPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.cryptoTokensPresent);

   encodeBit (pctxt, (ASN1BOOL)pvalue->m.integrityCheckValuePresent);


   stat = asn1PE_H225RequestSeqNum (pctxt, pvalue->requestSeqNum);
   if (stat != ASN_OK) return stat;


   if (pvalue->m.nonStandardDataPresent) {
      stat = asn1PE_H225NonStandardParameter (pctxt, &pvalue->nonStandardData);
      if (stat != ASN_OK) return stat;
   }


   stat = asn1PE_H225InfoRequestNakReason (pctxt, &pvalue->nakReason);
   if (stat != ASN_OK) return stat;


   if (pvalue->m.altGKInfoPresent) {
      stat = asn1PE_H225AltGKInfo (pctxt, &pvalue->altGKInfo);
      if (stat != ASN_OK) return stat;
   }


   if (pvalue->m.tokensPresent) {
      stat = asn1PE_H225_SeqOfH225ClearToken (pctxt, &pvalue->tokens);
      if (stat != ASN_OK) return stat;
   }


   if (pvalue->m.cryptoTokensPresent) {
      stat = asn1PE_H225_SeqOfH225CryptoH323Token (pctxt, &pvalue->cryptoTokens);
      if (stat != ASN_OK) return stat;
   }


   if (pvalue->m.integrityCheckValuePresent) {
      stat = asn1PE_H225ICV (pctxt, &pvalue->integrityCheckValue);
      if (stat != ASN_OK) return stat;
   }

   return (stat);
}
