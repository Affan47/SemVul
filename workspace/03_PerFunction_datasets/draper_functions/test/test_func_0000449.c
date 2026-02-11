verifyData(V,A a_)
{
  if (isSlotFiller(a_)==MSTrue)
   {
     P p; p.i=a_->p;
     A val=p.a[1];
     A attr=p.a[0];
     P pv; pv.i=val->p;
     int trueCount=0;
     if (val->t==Et&&val->n==0&&attr->t==Et&&attr->n==0) return MSTrue;
     for (int row=0;row<(int)val->n;row++)
      {
	if (QS(pv.a[row])) return MSFalse;
	else if (pv.a[row]->t!=It||pv.a[row]->r!=0) return MSFalse;
	else
         {
           if ((int)*pv.a[row]->p==1) trueCount++;
	   else if ((int)*pv.a[row]->p!=0) return MSFalse;
	 }
      }
     return (trueCount==0||trueCount>1)?MSFalse:MSTrue;
   }
  return MSFalse;
}
