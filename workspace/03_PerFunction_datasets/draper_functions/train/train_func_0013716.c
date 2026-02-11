DecodeEXTRQIMask(int Len, int Idx,
                      SmallVectorImpl<int> &ShuffleMask) {

  Len &= 0x3F;
  Idx &= 0x3F;


  if (0 != (Len % 8) || 0 != (Idx % 8))
    return;


  if (Len == 0)
    Len = 64;


  if ((Len + Idx) > 64) {
    ShuffleMask.append(16, SM_SentinelUndef);
    return;
  }


  Len /= 8;
  Idx /= 8;


  for (int i = 0; i != Len; ++i)
    ShuffleMask.push_back(i + Idx);
  for (int i = Len; i != 8; ++i)
    ShuffleMask.push_back(SM_SentinelZero);
  for (int i = 8; i != 16; ++i)
    ShuffleMask.push_back(SM_SentinelUndef);
}
