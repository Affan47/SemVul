MD5_string(char *string)
{
  struct MD5Context md5;
  size_t len = strlen(string);
  char* b = NULL;
  int i;

  MD5Init(&md5);
  MD5Update(&md5, (const unsigned char*)string, len);
  MD5Final(&md5);

#define MD5_LEN 16
  b = (char*)malloc(1+(MD5_LEN<<1));
  if(!b)
    return NULL;

  for(i = 0; i < MD5_LEN; i++)
    sprintf(b+(i<<1), "%02x", (unsigned int)md5.digest[i]);
  b[i<<1] = '\0';

  return b;
}
