_dxfNewPortHandle(tdmParsedFormatP format, Display **dpy)
#endif
{


  tdmPortHandleP	ret = NULL;
  tdmPortHandleP	(*_initP)();


#if defined(DX_NATIVE_WINDOWS)

  if (! _dxfHWload(&_initP))
      goto error;

  if(!(ret = (_initP)(format->where)))
    goto error;

#else

  ENTRY(("_dxfNewPortHandle(0x%x, 0x%x)", format, dpy));

  if (!*dpy) {
    if (((*dpy) = XOpenDisplay(format->where)) == NULL){

      DXSetError(ERROR_BAD_PARAMETER,"#13720",format->where);
      goto error;
    }
  }

  if(! _dxfHWload(&_initP, *dpy))
    goto error;


  PRINT(("_initP = 0x%x",_initP));
  PRINT(("*dpy = 0x%x",*dpy));
  PRINT(("format->where  = %s",format->where));
  if(!(ret = (_initP)(*dpy, format->where)))
    goto error;

#if !defined(DEBUG)


  DXHwddInterface(&_dxd_execHwddVersion);
  PRINT(("exec Version = %d,", _dxd_execHwddVersion));
  PRINT((" lm version = %d\n", _dxd_lmHwddVersion));
  if(_dxd_lmHwddVersion < _dxd_execHwddVersion) {
    DXErrorGoto(ERROR_UNEXPECTED,"#13920");
  }
#endif

  ret->dpy = (void*)*dpy;
#endif

  EXIT(("ret = 0x%x",ret));
  return ret;

error:
  if(ret) (ret->uninitP)(ret);
  ret = NULL;

#if !defined(DX_NATIVE_WINDOWS)
 if(*dpy) {
      XSync(*dpy,0);
      XCloseDisplay(*dpy);
    }
#endif

  EXIT(("ret = NULL"));
  return NULL;
}
