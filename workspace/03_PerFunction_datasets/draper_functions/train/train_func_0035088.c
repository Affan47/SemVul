binaryCompare(unsigned char aBinaryValue_,MSComparison aComparison_) const
{
  unsigned aSize=size();
  unsigned n=length();
  MSTypeData<unsigned char,MSAllocator<unsigned char> > *d=MSTypeData<unsigned char,MSAllocator<unsigned char> >::allocateWithSize(aSize);
  const unsigned char *ap=data();
  unsigned char *dp=d->elements();
  unsigned i;
  switch (aComparison_)
   {
   case MSLessThan:
     for (i=0;i<n;i++) dp[i]=(ap[i]<aBinaryValue_); break;
   case MSLessThanOrEqualTo:
     for (i=0;i<n;i++) dp[i]=(ap[i]<=aBinaryValue_); break;
   case MSEqualTo:
     for (i=0;i<n;i++) dp[i]=(ap[i]==aBinaryValue_); break;
   case MSNotEqualTo:
     for (i=0;i<n;i++) dp[i]=(ap[i]!=aBinaryValue_); break;
   case MSGreaterThan:
     for (i=0;i<n;i++) dp[i]=(ap[i]>aBinaryValue_); break;
   case MSGreaterThanOrEqualTo:
     for (i=0;i<n;i++) dp[i]=(ap[i]>=aBinaryValue_); break;
   }
  return MSBinaryMatrix(d,rows(),columns());
}
