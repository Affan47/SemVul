set(MSAttrValueList& avList_)
{
  MSCompositeField::set(avList_);
  MSIndexVector index;
  for(unsigned i=0;i<avList_.length();i++)
   {
     if (avList_[i].attribute()=="columns")
     columns(avList_[i].value().asInt()),index<<i;
   }
  avList_.remove(index);
}
