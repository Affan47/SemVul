redraw(void)
{
  if (owner()->mapped()==MSTrue&&owner()->frozen()==MSFalse)
   {
     drawBackground();
     drawSymbol();
     if (pixmap()==0) drawLabel();
     else drawPixmap();
     (armed()==MSTrue)?drawSunken():drawRaised();
   }
}
