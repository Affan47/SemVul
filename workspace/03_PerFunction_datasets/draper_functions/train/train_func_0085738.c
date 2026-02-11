wctomb(char * pC,int &length,UT_UCS4Char wc, int max_len )
{
  char* obuf = pC;
  const char* ibuf = reinterpret_cast<const char *>(&wc);

  size_t inlen = 4, outlen = max_len;
  size_t len = UT_iconv(cd,&ibuf,&inlen,&obuf,&outlen);
  if (len==(size_t)-1)
    return 0;
  length = max_len-outlen;
  return 1;
}
