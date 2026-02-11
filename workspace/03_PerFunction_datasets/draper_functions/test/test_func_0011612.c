encodeUnconsLength (OOCTXT* pctxt, ASN1UINT value)
{
   int enclen, stat;

   stat = encodeByteAlign (pctxt);
   if (stat != ASN_OK) return LOG_ASN1ERR (pctxt, stat);


   if (value < 128) {
      stat = encodeBits (pctxt, value, 8);
      enclen = (stat == ASN_OK) ? value : stat;
   }

   else if (value < 16384) {
      if ((stat = encodeBit (pctxt, 1)) == ASN_OK)
         stat = encodeBits (pctxt, value, 15);
      enclen = (stat == ASN_OK) ? value : stat;
   }

   else {
      int multiplier = ASN1MIN (value/16384, 4);
      encodeBit (pctxt, 1);
      encodeBit (pctxt, 1);
      stat = encodeBits (pctxt, multiplier, 6);
      enclen = (stat == ASN_OK) ? 16384 * multiplier : stat;
   }

   return enclen;
}
