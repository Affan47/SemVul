BraState_Code(void *pp, Byte *dest, SizeT *destLen, const Byte *src, SizeT *srcLen,
    int srcWasFinished, ECoderFinishMode finishMode, int *wasFinished)
{
  CBraState *p = ((CBraState *)pp);
  SizeT destLenOrig = *destLen;
  SizeT srcLenOrig = *srcLen;
  UNUSEDPARAM(finishMode);
  *destLen = 0;
  *srcLen = 0;
  *wasFinished = 0;
  while (destLenOrig > 0)
  {
    if (p->bufPos != p->bufConv)
    {
      size_t curSize = p->bufConv - p->bufPos;
      if (curSize > destLenOrig)
        curSize = destLenOrig;
      memcpy(dest, p->buf + p->bufPos, curSize);
      p->bufPos += curSize;
      *destLen += curSize;
      dest += curSize;
      destLenOrig -= curSize;
      continue;
    }
    p->bufTotal -= p->bufPos;
    memmove(p->buf, p->buf + p->bufPos, p->bufTotal);
    p->bufPos = 0;
    p->bufConv = 0;
    {
      size_t curSize = BRA_BUF_SIZE - p->bufTotal;
      if (curSize > srcLenOrig)
        curSize = srcLenOrig;
      memcpy(p->buf + p->bufTotal, src, curSize);
      *srcLen += curSize;
      src += curSize;
      srcLenOrig -= curSize;
      p->bufTotal += curSize;
    }
    if (p->bufTotal == 0)
      break;
    switch(p->methodId)
    {
      case XZ_ID_Delta:
        if (p->encodeMode)
          Delta_Encode(p->deltaState, p->delta, p->buf, p->bufTotal);
        else
          Delta_Decode(p->deltaState, p->delta, p->buf, p->bufTotal);
        p->bufConv = p->bufTotal;
        break;
      case XZ_ID_X86:
        p->bufConv = x86_Convert(p->buf, p->bufTotal, p->ip, &p->x86State, p->encodeMode);
        break;
      CASE_BRA_CONV(PPC)
      CASE_BRA_CONV(IA64)
      CASE_BRA_CONV(ARM)
      CASE_BRA_CONV(ARMT)
      CASE_BRA_CONV(SPARC)
      default:
        return SZ_ERROR_UNSUPPORTED;
    }
    p->ip += (UInt32)p->bufConv;

    if (p->bufConv == 0)
    {
      if (!srcWasFinished)
        break;
      p->bufConv = p->bufTotal;
    }
  }
  if (p->bufTotal == p->bufPos && srcLenOrig == 0 && srcWasFinished)
    *wasFinished = 1;
  return SZ_OK;
}
