compressRows(const MSBinaryVector& aBinaryVector_ )
{
  if (data()==0) return *this;
  if (aBinaryVector_.length()!=rows())
   {
     error("MSBinaryMatrix length error.");
     return *this;
   }

  unsigned newLength=(unsigned)(aBinaryVector_.sum()*columns());
  MSTypeData<unsigned char,MSAllocator<unsigned char> > *d=MSTypeData<unsigned char,MSAllocator<unsigned char> >::allocateWithLength(newLength);
  unsigned char *dp=d->elements();
  unsigned char *mp=data();
  unsigned i,j;
  for (i=0;i<rows();i++)
   {
     if (aBinaryVector_(i)==0) mp+=columns();
     else for (j=0;j<columns();j++) *dp++=*mp++;
   }
  freeData();
  _pData=d;
  _rows=(unsigned)aBinaryVector_.sum();
  _count=newLength;
  changed();
  return *this;
}
