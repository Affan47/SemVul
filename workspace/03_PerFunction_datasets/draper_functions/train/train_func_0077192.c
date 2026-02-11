AllocateColorTable(PictColorTable **colorTable,Display *disp,
		       Colormap cmap,int colormap_level,int ncolors,
		       int lut_start,char atom)
{
  int color_nb;
  int i,r;


  (*colorTable) = (PictColorTable*)ckalloc(sizeof(PictColorTable));
  if((*colorTable) == NULL) {
    (void)fprintf(stderr,"ImgPictGet: Could not allocate memory\n");
    return 0;
  }


  (*colorTable)->display = disp;
  (*colorTable)->colormap = cmap;
  (*colorTable)->colormap_level = colormap_level;
  (*colorTable)->ncolors = ncolors;
  (*colorTable)->lut_start = lut_start;
  (*colorTable)->atom =  atom;
  (*colorTable)->refCount = 1;

  color_nb = ncolors-1;

  for( i=0; i<MAX_LOOKUP; i++ )
    byteLookup[ i ] = i * 256 / MAX_LOOKUP;


  for (i=0; i<ncolors; i++) {
    (*colorTable)->intensity_lut[i] = i;
  }

  for (i=0; i<MAX_COLORS; i++) {
    (*colorTable)->red_lut[i] = i;
    (*colorTable)->green_lut[i] = i;
    (*colorTable)->blue_lut[i] = i;
  }
  for (i = 0; i < MAX_COLORS; ++i) {
    r = i*color_nb/(MAX_COLORS-1)+lut_start;
    (*colorTable)->redValues[i] = lut_colorcell_defs[r].pixel;
  }


  gray(disp,cmap,ncolors,lut_start,False,
       (*colorTable)->red,
       (*colorTable)->green,
       (*colorTable)->blue,
       (*colorTable)->intensity_lut,
       (*colorTable)->red_lut,
       (*colorTable)->green_lut,
       (*colorTable)->blue_lut);

  return 1;
}
