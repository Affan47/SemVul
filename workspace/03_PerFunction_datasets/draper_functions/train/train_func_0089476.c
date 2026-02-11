computePixmapYCoord(const MSPixmap *pixmap_)
{
  int offset=highlightThickness()+shadowThickness()+margin();
  int labelH=labelHeight();
  int pixmapH=pixmap_->height();
  int labelSp=computeLabelSpacing();
  int r=0;
  if (alignment()&MSTop)
   {
     if (labelAlignment()==MSTop) r=offset+labelH+labelSp;
     else if (labelAlignment()==MSBottom) r=offset;
     else
      {
	if (labelH<pixmapH) r=offset;
	else r=offset+(labelH-pixmapH)/2;
      }
   }
  else if (alignment()&MSBottom)
   {
     if (labelAlignment()==MSTop) r=height()-pixmapH-offset;
     else if (labelAlignment()==MSBottom) r=height()-labelH-pixmapH-labelSp-offset;
     else
      {
	if (labelH<pixmapH) r=height()-pixmapH-offset;
	else r=height()-labelH-offset+(labelH-pixmapH)/2;
      }
   }
  else
   {
     if (labelAlignment()==MSTop) r=(height()-(pixmapH+labelH+labelSp))/2+labelH+labelSp;
     else if (labelAlignment()==MSBottom) r=(height()-(pixmapH+labelH+labelSp))/2;
     else r=(height()-pixmapH)/2;
   }
  return r;
}
