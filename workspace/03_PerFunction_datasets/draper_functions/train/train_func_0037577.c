update(const MSIndexVector& index_)
{
  if (MSView::model()!=0)
   {
     if (index_.length()==0)
      {
	 if (dynamic()==MSTrue) computeSize();
	 else redraw();
      }
     else if (frozen()==MSFalse&&mapped()==MSTrue)
      {
	if (numberOfRows()!=numRows())
	 {
	   if (dynamic()==MSTrue) computeSize();
	   else redraw();
	 }
        else
	 {
	   if (dynamic()==MSTrue) computeSize();
	   else
	    {
	      for (unsigned i=0;i<index_.length();i++)
	       {
		 clearRow(index_(i));
		 drawRow(index_(i));
	       }
	    }
	   XFlush(display());
	 }
      }
     _numberOfRows=numRows();
   }
}
