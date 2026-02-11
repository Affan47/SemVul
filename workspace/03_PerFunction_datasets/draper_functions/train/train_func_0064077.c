der_put_unsigned64 (unsigned char *p, size_t len, const uint64_t *v, size_t *size)
{
    unsigned char *base = p;
    uint64_t val = *v;

    if (val) {
       while (len > 0 && val) {
           *p-- = val % 256;
           val /= 256;
           --len;
       }
       if (val != 0)
           return ASN1_OVERFLOW;
       else {
           if(p[1] >= 128) {
               if(len < 1)
                   return ASN1_OVERFLOW;
               *p-- = 0;
           }
           *size = base - p;
           return 0;
       }
    } else if (len < 1)
       return ASN1_OVERFLOW;
    else {
       *p    = 0;
       *size = 1;
       return 0;
    }
}
