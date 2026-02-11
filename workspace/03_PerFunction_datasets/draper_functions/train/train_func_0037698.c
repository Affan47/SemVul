drawPixmap(void)
{
   if (mapped()==MSTrue)
   {
      const MSPixmap *pmap;
      if (armed()==MSTrue) pmap=armedPixmap();
      else if (sensitive()==MSTrue) pmap=pixmap();
      else pmap=insensitivePixmap();
      if (pmap!=0)
       {
	 int startx=computePixmapXCoord(pmap);
	 int starty=computePixmapYCoord(pmap);
         GC gc=pixmapGC();
	 XSetForeground(display(),gc,foreground());
	 if (armed()==MSTrue) XSetBackground(display(),gc,selectShadowColor());
	 else XSetBackground(display(),gc,background());
	 copyPixmap(display(),*pmap,window(),gc,startx,starty);
       }
    }
}
