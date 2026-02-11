drawLabel(void)
{
  if (mapped()==MSTrue)
   {
     if (armed()==MSTrue)
      {
        if (depth()==1)
         {
           XSetForeground(display(),textGC(),background());
           XSetBackground(display(),textGC(),foreground());
           MSLabel::drawLabel();
         }
        else
         {
           XSetBackground(display(),textGC(),selectShadowColor());
           MSLabel::drawLabel();
         }
      }
     else
      {
        XSetBackground(display(),textGC(),background());
        MSLabel::drawLabel();
      }
   }
}
