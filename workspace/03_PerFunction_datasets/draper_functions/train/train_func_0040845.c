bincmp_utf8mb4(const uchar *s, const uchar *se,
               const uchar *t, const uchar *te)
{
  int slen= (int) (se - s), tlen= (int) (te - t);
  int len= min(slen, tlen);
  int cmp= memcmp(s, t, len);
  return cmp ? cmp : slen - tlen;
}
