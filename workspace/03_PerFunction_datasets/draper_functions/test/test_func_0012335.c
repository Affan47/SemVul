makeNonCurrent(){
#ifdef HAVE_GL_H
  if(ctx){
#ifndef WIN32
    return glXMakeCurrent((Display*)getApp()->getDisplay(),None,(GLXContext)NULL);
#else


    ::ReleaseDC((HWND)xid,wglGetCurrentDC());
    BOOL bStatus=wglMakeCurrent(NULL,NULL);
    return bStatus;
#endif
    }
#endif
  return FALSE;
  }
