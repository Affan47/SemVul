asn1PE_H235EncodedGeneralToken (OOCTXT* pctxt, H235EncodedGeneralToken value)
{
   int stat = ASN_OK;

   stat = encodeOpenType (pctxt, value.numocts, value.data);
   if (stat != ASN_OK) return stat;

   return (stat);
}
