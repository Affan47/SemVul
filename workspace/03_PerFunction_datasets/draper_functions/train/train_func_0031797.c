asn1PD_H235ECKASDH_eckasdh2 (OOCTXT* pctxt, H235ECKASDH_eckasdh2* pvalue)
{
   int stat = ASN_OK;


   invokeStartElement (pctxt, "public_key", -1);

   stat = asn1PD_H235ECpoint (pctxt, &pvalue->public_key);
   if (stat != ASN_OK) return stat;

   invokeEndElement (pctxt, "public_key", -1);


   invokeStartElement (pctxt, "fieldSize", -1);

   stat = asn1PD_H235ECKASDH_eckasdh2_fieldSize (pctxt, &pvalue->fieldSize);
   if (stat != ASN_OK) return stat;

   invokeEndElement (pctxt, "fieldSize", -1);


   invokeStartElement (pctxt, "base", -1);

   stat = asn1PD_H235ECpoint (pctxt, &pvalue->base);
   if (stat != ASN_OK) return stat;

   invokeEndElement (pctxt, "base", -1);


   invokeStartElement (pctxt, "weierstrassA", -1);

   stat = asn1PD_H235ECKASDH_eckasdh2_weierstrassA (pctxt, &pvalue->weierstrassA);
   if (stat != ASN_OK) return stat;

   invokeEndElement (pctxt, "weierstrassA", -1);


   invokeStartElement (pctxt, "weierstrassB", -1);

   stat = asn1PD_H235ECKASDH_eckasdh2_weierstrassB (pctxt, &pvalue->weierstrassB);
   if (stat != ASN_OK) return stat;

   invokeEndElement (pctxt, "weierstrassB", -1);

   return (stat);
}
