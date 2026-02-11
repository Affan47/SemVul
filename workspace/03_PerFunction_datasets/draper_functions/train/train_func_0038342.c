_base64_decode_internal(const unsigned char *in,  unsigned long inlen,
                                 unsigned char *out, unsigned long *outlen,
                           const unsigned char *map)
{
   unsigned long t, x, y, z;
   unsigned char c;
   int           g;

   LTC_ARGCHK(in     != NULL);
   LTC_ARGCHK(out    != NULL);
   LTC_ARGCHK(outlen != NULL);

   g = 3;
   for (x = y = z = t = 0; x < inlen; x++) {
       c = map[in[x]&0xFF];
       if (c == 255) continue;

       if (c == 254) {
          c = 0;

          if (--g < 0) {
             return CRYPT_INVALID_PACKET;
          }
       } else if (g != 3) {

          return CRYPT_INVALID_PACKET;
       }

       t = (t<<6)|c;

       if (++y == 4) {
          if (z + g > *outlen) {
             return CRYPT_BUFFER_OVERFLOW;
          }
          out[z++] = (unsigned char)((t>>16)&255);
          if (g > 1) out[z++] = (unsigned char)((t>>8)&255);
          if (g > 2) out[z++] = (unsigned char)(t&255);
          y = t = 0;
       }
   }
   if (y != 0) {
       return CRYPT_INVALID_PACKET;
   }
   *outlen = z;
   return CRYPT_OK;
}
