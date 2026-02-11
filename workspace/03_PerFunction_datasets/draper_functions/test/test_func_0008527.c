insertRowAfter(unsigned row_,const MSBinaryVector& aBinaryVector_)
{
  if (row_>rows()) return *this;
  if (aBinaryVector_.length()!=columns())
   {
     error("MSBinaryMatrix length error.");
     return *this;
   }

  unsigned newLength=(rows()+1)*columns();
  MSTypeData<unsigned char,MSAllocator<unsigned char> > *d=MSTypeData<unsigned char,MSAllocator<unsigned char> >::allocateWithLength(newLength);
  unsigned char *dp=d->elements();
  unsigned char *mp=data();
  unsigned char *vp=aBinaryVector_.data();
  unsigned i,j;

  for (j=0;j<rows()+1;j++)
   {
     for (i=0;i<columns();i++) *dp++=(j==row_+1)?*vp++:*mp++;
   }
  freeData();
  _pData=d;
  _rows++;
  _count=newLength;
  changed();
  return *this;
}
