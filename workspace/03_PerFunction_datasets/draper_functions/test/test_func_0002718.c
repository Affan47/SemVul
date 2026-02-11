printImageString(GC gc_,int x_,int y_,const char *string_,int n_)
{
  if (n_!=0)
   {
     updateGC(gc_);
     setFontAttributes();
     if (printMode()==Colorfg) gcValues().background=whitePixel();
     if (printMode()==Color||printMode()==Colorfg) setBackground(-1);
     else setBackground();
     printRectangle(x_org()+x_,owner()->height()-y_org()-y_+fontInfo()->ascent,XTextWidth(fontInfo(),string_,n_),
		    fontHeight()
		   );
     pout<< "f";
     pout<< endl;
     setForeground();
     pout<< endl;
     printString(x_org()+x_,owner()->height()-y_org()-y_,string_,n_);
   }
}
