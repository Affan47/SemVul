DisposeColorTable(PictColorTable *colorTable)
{
  unsigned long *pixels;
  int i,j;


  if(colorTable->refCount != 0 ||  colorTable->colormap_level == POW_COLORMAP)
    return 0;


  if(colorTable->atom == 1)
    deinit_disp(colorTable->display);

  if(colorTable->colormap_level > READ_SHARED_COLORMAP) {

    pixels = (unsigned long *)ckalloc(colorTable->ncolors*
				     sizeof(unsigned long));
    if( pixels == NULL )
      return 0;


    for(j=colorTable->lut_start,i=0;i<colorTable->ncolors;i++,j++)
      pixels[i] = j;


    XFreeColors(colorTable->display,colorTable->colormap,
		pixels,colorTable->ncolors,0);
    ckfree((void*)pixels);


    XFreeColormap(colorTable->display,
		  colorTable->colormap);
  }

  if( colorTable->colormap_level ==  READ_SHARED_COLORMAP )
    Default_Shared_Allocated = 0;
  if( colorTable->colormap_level == DEFAULT_SCREEN_COLORMAP)
    Default_Screen_Allocated = 0;
  else if( colorTable->colormap_level == DEFAULT_PRIVATE_COLORMAP )
    Default_Private_Allocated = 0;

  ckfree((void*)colorTable);
  colorTable = NULL;

  return 1;
}
