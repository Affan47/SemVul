hash(const char *s)
#else
hash(s)
    char *s;
#endif
{
    unsigned long sum = 0, wd;
    unsigned j;

    if(sixclash) {
      unsigned i = 0;
      while (i < 6 && s[i] != '\0') {
         wd = 0;
         for(j=1; j <= sizeof(long) && i < 6 && s[i] != '\0'; i++,j++) {
            wd += (unsigned long)(s[i] & 0xff) << (sizeof(long) - j) * 8;}

	sum ^= wd;}
    }
    else {
      while( *s != '\0' ) {
         wd = 0;
         for(j=1; j <= sizeof(long) && *s != '\0'; j++) {
            wd += (unsigned long)(*s++ & 0xff) << (sizeof(long) - j) * 8;}

	sum ^= wd;}
    }
    return sum;
}
