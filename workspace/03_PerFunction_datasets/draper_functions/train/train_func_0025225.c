mgx11_ctxcreate( int a1, ... )
{
  va_list alist;

  _mgc =
    (mgcontext*)mgx11_newcontext( OOGLNewE(mgx11context, "mgx11_ctxcreate") );

  if (!Xmg_initx11device())
    OOGLError(0,"mgdevice_X11: unable to open X-display");

  va_start(alist, a1);
  if (_mgx11_ctxset(a1, &alist) == -1) {
    mgx11_ctxdelete(_mgc);
  }
  va_end(alist);
  return _mgc;
}
