rowSpan(int index_,A am_,int *row_,int *span_)
{
  int r=0;
  int c=0;
  int w=(int)am_->d[1];
  int span=0;
  int row=0;
  P p; p.i=am_->p;

  if (am_->r==2)
   {
     for (c=0;c<am_->d[1]&&span==0;c++)
      {
	for (r=0;r<am_->d[0];r++)
	 {
	   if (p.i[r*w+c]==index_)
	    {
	      if (span==0) row=r;
	      span++;
	    }
	 }
      }
   }
  *row_=row;
  *span_=span;
}
