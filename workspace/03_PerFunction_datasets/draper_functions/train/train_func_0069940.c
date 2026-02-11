LzmaDecode(Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen,
    const Byte *propData, unsigned propSize, ELzmaFinishMode finishMode,
    ELzmaStatus *status, ISzAlloc *alloc)
{
  CLzmaDec p;
  SRes res;
  SizeT inSize = *srcLen;
  SizeT outSize = *destLen;
  *srcLen = *destLen = 0;
  if (inSize < RC_INIT_SIZE)
    return SZ_ERROR_INPUT_EOF;

  LzmaDec_Construct(&p);
  res = LzmaDec_AllocateProbs(&p, propData, propSize, alloc);
  if (res != 0)
    return res;
  p.dic = dest;
  p.dicBufSize = outSize;

  LzmaDec_Init(&p);

  *srcLen = inSize;
  res = LzmaDec_DecodeToDic(&p, outSize, src, srcLen, finishMode, status);

  if (res == SZ_OK && *status == LZMA_STATUS_NEEDS_MORE_INPUT)
    res = SZ_ERROR_INPUT_EOF;

  (*destLen) = p.dicPos;
  LzmaDec_FreeProbs(&p, alloc);
  return res;
}
