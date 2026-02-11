asn1PE_H225EndpointIdentifier (OOCTXT* pctxt, H225EndpointIdentifier value)
{
   static Asn1SizeCnst lsize1 = { 0, 1, 128, 0 };
   int stat = ASN_OK;

   addSizeConstraint (pctxt, &lsize1);

   stat = encodeBMPString (pctxt, value, 0);
   if (stat != ASN_OK) return stat;

   return (stat);
}
