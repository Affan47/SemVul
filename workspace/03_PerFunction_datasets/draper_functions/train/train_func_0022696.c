_dxf_SET_WINDOW_SIZE (void *win, int w, int h)
{
  DEFWINDATA(win) ;
  DEFPORT(PORT_HANDLE) ;

  ENTRY(("_dxf_SET_WINDOW_SIZE (0x%x, %d, %d)",
	 win, w, h));

    WINHEIGHT = h ;
  WINWIDTH = w ;

#if defined(DX_NATIVE_WINDOWS)
  MoveWindow(XWINID, 0, 0, w, h, FALSE);
  _dxf_SET_VIEWPORT (PORT_CTX, 0, w-1, 0, h-1) ;
#else
  if(!getenv("IGNORE_GLXWAITX"))
  glXWaitGL() ;

  XResizeWindow (DPY, XWINID, w, h) ;

  if(!getenv("IGNORE_GLXWAITX"))
  glXWaitX() ;

  _dxf_SET_VIEWPORT (PORT_CTX, 0, w-1, 0, h-1) ;
#endif

  OGL_FAIL_ON_ERROR(_dxf_SET_WINDOW_SIZE);
  EXIT((""));
}
