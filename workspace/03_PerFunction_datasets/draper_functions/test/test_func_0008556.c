computeSize(void)
{
  int widthOffset=(highlightThickness()+shadowThickness()+marginWidth())<<1;
  int heightOffset=(highlightThickness()+shadowThickness()+marginHeight())<<1;
  if (pixmap()==0)
  {
     resize (fontObject()->textWidth(label(),label().length())+(arrow()->width()<<1)+widthOffset+indent(),
	     fontObject()->textHeight()+heightOffset);
  }
  else
  {
     resize (pixmap()->width()+(arrow()->width()<<1)+widthOffset,pixmap()->height()+heightOffset);
  }

}
