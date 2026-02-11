printFillRectangle(GC gc_,int x_,int y_,int w_,int h_,MSBoolean fill_)
{
  updateGC(gc_);
  if (printMode()==Colorfg&&fill_!=MSTrue) gcValues().foreground=whitePixel();
  setBackground(printMode()!=Color&&fill_==MSTrue?1:0);
  printRectangle(x_org()+x_,owner()->height()-y_org()-y_,w_,h_);
  pout<< "f";
  pout<< endl;
}
