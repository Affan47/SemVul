_dxf_getHwScreenView(screenO ob, dxScreen* s, dxObject* subObject,
		   float mvm[4][4], float mm[4][4],
		   int* width, int* height)
{
  screenT *sp;

  ENTRY(("_dxf_getScreenView(0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x)",
	 sp, s, subObject, mvm, mm, width, height));

  if (! ob)
      return NULL;

  sp = (screenT *)_dxf_getHwObjectData(ob);

  if(s)
    *s = sp->screen;

  if(width)
    *width = sp->width;

  if(height)
    *height = sp->height;

  if(subObject)
    *subObject = sp->subObject;

  if(mvm)
    COPYMATRIX(mvm,(sp->mvm));

  if(mm)
    COPYMATRIX(mm,(sp->mm));

  EXIT(("sp = 0x%x",sp));
  return ob;
}
