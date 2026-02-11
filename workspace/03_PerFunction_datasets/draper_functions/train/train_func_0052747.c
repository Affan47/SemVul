drawRows(int rs_,int re_,int cs_,int ce_)
{
  if (mapped()==MSTrue&&frozen()==MSFalse)
   {
     rs_=(rs_>=firstRow())?rs_:firstRow();
     re_=(re_<=lastRow())?re_:lastRow();
     cs_=(cs_>=firstColumn())?cs_:firstColumn();
     ce_=(ce_<=lastColumn())?ce_:lastColumn();
     drawRows(panner()->window(),rs_,re_,cs_,ce_);
   }
}
