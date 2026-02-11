lGetPosType(const lDescr *dp, int pos)
{
   if (!dp ) {
      LERROR(LEDESCRNULL);
      return (int) NoName;
   }
   if (pos < 0) {
      return (int) NoName;
   }
   return mt_get_type(dp[pos].mt);
}
