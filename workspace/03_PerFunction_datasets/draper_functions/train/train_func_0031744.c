insertRowBefore(unsigned row_,unsigned char fill_)
{
  if (row_+1>rows()) return *this;

  unsigned newLength=(rows()+1)*columns();
  MSTypeData<unsigned char,MSAllocator<unsigned char> > *d=MSTypeData<unsigned char,MSAllocator<unsigned char> >::allocateWithLength(newLength);
  unsigned char *dp=d->elements();
  unsigned char *mp=data();
  unsigned i,j;
  unsigned char fill=fill_>0?1:0;

  for (j=0;j<rows()+1;j++)
   {
     for (i=0;i<columns();i++) *dp++=(j==row_)?fill:*mp++;
   }
  freeData();
  _pData=d;
  _rows++;
  _count=newLength;
  changed();
  return *this;
}
