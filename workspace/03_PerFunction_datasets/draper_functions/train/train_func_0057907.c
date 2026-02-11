set(MSAttrValueList& avList_)
{
  MSMenu::set(avList_);
  MSIndexVector index;
  for (int i=0;i<avList_.length();i++)
   {
     if(avList_[i].attribute()=="orientation")
      {
        if(avList_[i].value()=="Horizontal") orientation(Horizontal);
        else orientation(Vertical);
        index<<i;
      }
   }
  avList_.remove(index);

}
