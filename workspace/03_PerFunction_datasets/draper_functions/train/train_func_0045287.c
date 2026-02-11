asn1PE_H225BandwidthDetails (OOCTXT* pctxt, H225BandwidthDetails* pvalue)
{
   int stat = ASN_OK;
   ASN1BOOL extbit;


   extbit = 0;

   encodeBit (pctxt, extbit);


   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->sender);
   if (stat != ASN_OK) return stat;


   stat = encodeBit (pctxt, (ASN1BOOL)pvalue->multicast);
   if (stat != ASN_OK) return stat;


   stat = asn1PE_H225BandWidth (pctxt, pvalue->bandwidth);
   if (stat != ASN_OK) return stat;


   stat = asn1PE_H225TransportChannelInfo (pctxt, &pvalue->rtcpAddresses);
   if (stat != ASN_OK) return stat;

   return (stat);
}
