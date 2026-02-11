fl_init_xim() {
  static int xim_warning = 2;
  if (xim_warning > 0) xim_warning--;


  XIMStyles *xim_styles;
  if (!fl_display) return;
  if (fl_xim_im) return;

  fl_xim_im = XOpenIM(fl_display, NULL, NULL, NULL);
  xim_styles = NULL;
  fl_xim_ic = NULL;

  if (fl_xim_im) {
    XGetIMValues (fl_xim_im, XNQueryInputStyle,
                  &xim_styles, NULL, NULL);
  } else {
    if (xim_warning)
      Fl::warning("XOpenIM() failed");

    if (xim_styles) XFree(xim_styles);
    return;
  }

  if (xim_styles && xim_styles->count_styles) {
    fl_new_ic();
   } else {
     if (xim_warning)
       Fl::warning("No XIM style found");
     XCloseIM(fl_xim_im);
     fl_xim_im = NULL;

     if (xim_styles) XFree(xim_styles);
     return;
  }
  if (!fl_xim_ic) {
    if (xim_warning)
      Fl::warning("XCreateIC() failed");
    XCloseIM(fl_xim_im);
    fl_xim_im = NULL;
  }

  if(xim_styles) XFree(xim_styles);
}
