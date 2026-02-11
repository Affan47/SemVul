drawAreaShadow(void)
{
  if (shadowThickness()>0)
   {
     int viewWidth=width()-highlightThickness()*2;
     viewWidth-=(vsb()->mapped()==MSTrue)?vsb()->width():0;
     int viewHeight=height()-highlightThickness()*2;
     viewHeight-=(hsb()->mapped()==MSTrue)?hsb()->height():0;
     drawBevel(window(),MSRect(highlightThickness(),highlightThickness(),viewWidth,viewHeight),shadowStyle(),shadowThickness());
   }
}
