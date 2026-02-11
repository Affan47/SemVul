asn1PD_H235EncodedGeneralToken (OOCTXT* pctxt, H235EncodedGeneralToken* pvalue)
{
   int stat = ASN_OK;

   stat = decodeOpenType (pctxt, &pvalue->data, &pvalue->numocts);
   if (stat != ASN_OK) return stat;
   invokeOpenTypeValue
      (pctxt, pvalue->numocts, pvalue->data);

   return (stat);
}
