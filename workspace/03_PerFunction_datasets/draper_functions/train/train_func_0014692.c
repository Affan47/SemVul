columns(unsigned columns_)
{
  if (columns_>0&&_columns!=columns_)
   {
     _columns=columns_;
     computeSize();
   }
}
