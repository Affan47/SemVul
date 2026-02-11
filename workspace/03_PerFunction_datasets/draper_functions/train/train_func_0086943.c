decodeUTF8(const char *bytes, long *ucs, int ucs_max_len)
{
  if (!bytes) return 0;
  int num_bytes = strlen(bytes), num_chars=0, i=0;
  unsigned char *b = (unsigned char *)bytes;

  bytes += num_bytes;
  while(b < (unsigned char *)bytes && num_chars < ucs_max_len) {
    if(*b<=127) ucs[num_chars++] = *b;
    else if(*b<=192) { printf("invalid utf-8 data\n"); }
    else if(*b<=223) ucs[num_chars++] = ((*b-192)<<6) + (*++b-128);
    else if(*b<=239) ucs[num_chars++] = ((*b-224)<<12) + ((*++b-128)<<6) + (*++b-128);
    else if(*b<=247) ucs[num_chars++] = ((*b-240)<<18) + ((*++b-128)<<12) + ((*++b-128)<<6) + (*++b-128);
    else if(*b<=251)
      ucs[num_chars++] = ((*b-248)<<24) + ((*++b-128)<<18) + ((*++b-128)<<12) + ((*++b-128)<<6) + (*++b-128);
    else if(*b<=253)
      ucs[num_chars++] = ((*b-252)<<30) + ((*++b-128)<<24)  + ((*++b-128)<<18) + ((*++b-128)<<12) + ((*++b-128)<<6) + (*++b-128);
    else { printf("invalid utf-8 data\n"); }
    b++;
  }
  return num_chars;
}
