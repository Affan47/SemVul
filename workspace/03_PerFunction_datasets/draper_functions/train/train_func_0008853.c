lastIndexOf(unsigned char aValue_,unsigned startPos_) const
{
  if (length()>0)
   {
     unsigned i;
     if (startPos_>=length()) i=length()-1;
     else i=startPos_;
     for (;i!=0;i--) if (elementAt(i)==aValue_) return i;
     if (i==0) if (elementAt(i)==aValue_) return i;
   }
  return length();
}
