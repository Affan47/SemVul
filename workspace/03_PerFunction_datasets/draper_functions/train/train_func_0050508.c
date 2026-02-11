computePageIndices(int i_,int& ri_,int& ci_)
{
  if (stackPageBreak().length()>0)
   {
     ci_=0;
     if (stackCount()<stackPageBreak().length())
      {
        int rowoffset=0;
        int coloffset=0;
        if (i_>=stackPageBreak()(stackCount()))
         {
           rowoffset=stackCount()+1;
           coloffset=stackCount()+1;
         }
        ri_=i_+rowoffset;
        ci_=coloffset;
      }
     else ri_=i_;
   }
  else
   {
     if (outputStyle()==RowMajor)
      {
        int pageCountRow=rowPageBreak().length()-1;
        ri_=i_>=pageCountRow?i_%pageCountRow:i_;
        ci_=(int)i_/pageCountRow;
      }
     else
      {
        int pageCountCol=columnPageBreak().length()-1;
        ci_=i_>=pageCountCol?i_%pageCountCol:i_;
        ri_=(int)i_/pageCountCol;
      }
   }
}
