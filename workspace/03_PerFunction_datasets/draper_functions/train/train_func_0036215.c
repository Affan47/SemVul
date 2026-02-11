Hc4_MatchFinder_Skip(CMatchFinder *p, LZ_UInt32 num)
{
  do
  {
    LZ_UInt32 hash2Value, hash3Value;
    SKIP_HEADER(4)
    HASH4_CALC;
    curMatch = p->hash[kFix4HashSize + hashValue];
    p->hash[                hash2Value] =
    p->hash[kFix3HashSize + hash3Value] =
    p->hash[kFix4HashSize + hashValue] = p->pos;
    p->son[p->cyclicBufferPos] = curMatch;
    MOVE_POS
  }
  while (--num != 0);
}
