asn1PD_H235CryptoToken_cryptoSignedToken_token (OOCTXT* pctxt, H235CryptoToken_cryptoSignedToken_token* pvalue)
{
   int stat = ASN_OK;


   invokeStartElement (pctxt, "toBeSigned", -1);

   stat = asn1PD_H235EncodedGeneralToken (pctxt, &pvalue->toBeSigned);
   if (stat != ASN_OK) return stat;

   invokeEndElement (pctxt, "toBeSigned", -1);


   invokeStartElement (pctxt, "algorithmOID", -1);

   stat = decodeObjectIdentifier (pctxt, &pvalue->algorithmOID);
   if (stat != ASN_OK) return stat;
   invokeOidValue (pctxt, pvalue->algorithmOID.numids, pvalue->algorithmOID.subid);

   invokeEndElement (pctxt, "algorithmOID", -1);


   invokeStartElement (pctxt, "paramS", -1);

   stat = asn1PD_H235Params (pctxt, &pvalue->paramS);
   if (stat != ASN_OK) return stat;

   invokeEndElement (pctxt, "paramS", -1);


   invokeStartElement (pctxt, "signature", -1);

   stat = decodeDynBitString (pctxt, (ASN1DynBitStr*)&pvalue->signature);
   if (stat != ASN_OK) return stat;

   invokeBitStrValue (pctxt, pvalue->signature.numbits, pvalue->signature.data);

   invokeEndElement (pctxt, "signature", -1);

   return (stat);
}
