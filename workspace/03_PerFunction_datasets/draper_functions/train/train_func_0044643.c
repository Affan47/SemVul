destroySharedColorAtom(Display *disp)
{
  Atom       colormapAtom;

#ifdef DEBUG
  printf("destroySharedColorAtom\n");
#endif


  colormapAtom = XInternAtom (disp, "VIEW_COLORMAP", True);

  if (colormapAtom == None) {
    printf("ERROR in destroySharedColorAtom: XInternAtom returned None (%d)\n",
	   (int)colormapAtom);
  }


  XDeleteProperty (disp, root_window, colormapAtom);
  return;
}
