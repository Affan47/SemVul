itemForeground(unsigned row_)
{
  unsigned long fg = foreground();
  V v = (model()!=0)?model()->aplusVar():0;
  int n = (model()!=0)?model()->numElmts():0;
  if (v!=0 && n ==2)
   {
     AColorFunction *fgFunc=AplusModel::getFgFunc(v);
     if (fgFunc!=0)
      {
	P p; p.i=model()->data();
	A as=p.a[0];
	A av=p.a[1];
        if (row_>=0&&row_<(int)av->n)
	  fg = fgFunc->invoke(v,(A)av->p[row_], (A) as->p[row_]);
      }
   }
  return fg;
}
