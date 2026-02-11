remainingrightmost(unsigned long merbytes,
                                       unsigned long byteoffset,
                                       GtUchar remainmask,
                                       GtUchar code,
                                       const GtUchar *leftptr,
                                       const GtUchar *rightptr)
{
  unsigned long len;
  GtUchar midcode;
  const GtUchar *midptr;

  while (leftptr + merbytes < rightptr)
  {
    len = (unsigned long) (rightptr-leftptr)/GT_MULT2(merbytes);
    midptr = leftptr + merbytes * len;
    midcode = extractremainingbytes(remainmask,byteoffset,midptr);
    if (code >= midcode)
    {
      leftptr = midptr;
    } else
    {
      rightptr = midptr;
    }
  }
  return leftptr;
}
