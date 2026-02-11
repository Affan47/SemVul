glUseFXFont(FXFont* font,int first,int count,int list){
  if(!font || !font->id()){ fxerror("glUseFXFont: invalid font.\n"); }
  FXTRACE((100,"glUseFXFont: first=%d count=%d list=%d\n",first,count,list));
#ifdef HAVE_GL_H
#ifndef WIN32
#ifdef HAVE_XFT_H
  glXUseXftFont((XftFont*)font->id(),first,count,list);
#else
  glXUseXFont((Font)font->id(),first,count,list);
#endif
#else
  HDC hdc=wglGetCurrentDC();
  HFONT oldfont=(HFONT)SelectObject(hdc,(HFONT)font->id());


  FXbool result=wglUseFontBitmaps(hdc,first,count,list);
  SelectObject(hdc,oldfont);
#endif
#endif
  }

}
