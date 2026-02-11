_dxfFreeAxesHandle(Pointer p)
{

  struct axes_struct *axeshandle = (struct axes_struct *)p;

  if (p) {
     DXFree(axeshandle);
  }
  return OK;
}
