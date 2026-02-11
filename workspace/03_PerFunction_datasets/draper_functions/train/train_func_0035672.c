get_font_height(Display *display, Font font)

{
  int rv = 0;
  XFontStruct *fstruct = NULL;

  fstruct = XQueryFont(display, font);
  if(!fstruct) {
    fprintf(stderr, "font_height: font %ld does not exist.\n", font);
    goto ERROR;
  }

  rv = fstruct->ascent + fstruct->descent;

 DONE:
  if(fstruct)
    XFreeFontInfo(NULL, fstruct, 1);
  return(rv);

 ERROR:
  rv = 1;
  goto DONE;
}
