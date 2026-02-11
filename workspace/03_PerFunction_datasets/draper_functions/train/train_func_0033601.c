ChangeColorTable(PictMaster *masterPtr)
{
  PictInstance *instancePtr = masterPtr->instancePtr;
  PictColorTable *colorTable;
  PictColorTable *old_colorTable;
  XVisualInfo *visInfoPtr;
  XRectangle validBox;

#ifdef DEBUG
  printf("ChangeColorTable \n");
#endif

  old_colorTable = instancePtr->colorTable;
  old_colorTable->refCount--;
  if ( old_colorTable->refCount == 0 ) {
    DisposeColorTable((PictColorTable *)old_colorTable);
  }

  if( GetColorTable(instancePtr->tkwin,(PictColorTable **)&colorTable,
		    (XVisualInfo **)&visInfoPtr) == 0 ) {
    fprintf(stderr," GetColorTable failed \n");
    return 0;
  }

  instancePtr->display = colorTable->display;
  instancePtr->colormap = colorTable->colormap;
  instancePtr->colormap_level = colorTable->colormap_level;
  instancePtr->has_overlay = 0;
  instancePtr->colorTable = colorTable;
  instancePtr->visualInfo = *visInfoPtr;
  XFree(visInfoPtr);

  XClipBox(masterPtr->validRegion, &validBox);
  if ((validBox.width > 0) && (validBox.height > 0)) {
    DitherInstance(instancePtr, validBox.x, validBox.y, validBox.width,
		   validBox.height);
  }

  Tk_ImageChanged(masterPtr->tkMaster, 0, 0,
		  masterPtr->width, masterPtr->height,
		  masterPtr->width, masterPtr->height);
  return 1;

}
