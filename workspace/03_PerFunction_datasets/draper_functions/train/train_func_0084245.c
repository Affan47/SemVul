rowLabel(int row_)
{
  static MSString buf;
  A outStr=aplus_nl;
  V v = (model()!=0)?((AplusModel *)model())->aplusVar():0;

  if (v!=0)
   {
     AOutFunction *titleFunc=AplusModel::getTitleFunc(v);
     if (titleFunc!=0)
      {
        outStr=(A)titleFunc->invoke(v,(A)aplus_nl,row_,-1);
        outStr=(outStr->t==Ct)?outStr:aplus_nl;
      }
     else if (row_>=0)
      {
	buf = MSInt(row_).asString();
	outStr=gsv(0,(char *)(const char *) buf);
      }
   }
  return outStr;
}
