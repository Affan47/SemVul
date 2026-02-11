encodebitsFromOctet (OOCTXT* pctxt, ASN1OCTET value, ASN1UINT nbits)
{
   int lshift = pctxt->buffer.bitOffset;
   int rshift = 8 - pctxt->buffer.bitOffset;
   int stat = ASN_OK;
   ASN1OCTET mask = 0x0;

   if (nbits == 0) return ASN_OK;


   if (nbits < 8) {
      switch (nbits) {
      case 1: mask = 0x80; break;
      case 2: mask = 0xC0; break;
      case 3: mask = 0xE0; break;
      case 4: mask = 0xF0; break;
      case 5: mask = 0xF8; break;
      case 6: mask = 0xFC; break;
      case 7: mask = 0xFE; break;
      default:;
      }
      value &= mask;
   }


   if (pctxt->buffer.bitOffset == 8) {
      pctxt->buffer.data[pctxt->buffer.byteIndex] = value;
      if (nbits == 8) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] = 0;
      }
      else
         pctxt->buffer.bitOffset -= nbits;
   }


   else {
      pctxt->buffer.data[pctxt->buffer.byteIndex] |=
         (ASN1OCTET)(value >> rshift);

      pctxt->buffer.bitOffset -= nbits;

      if (pctxt->buffer.bitOffset < 0) {
         pctxt->buffer.byteIndex++;
         pctxt->buffer.data[pctxt->buffer.byteIndex] =
            (ASN1OCTET)(value << lshift);
         pctxt->buffer.bitOffset += 8;
      }
   }

   return stat;
}
