fl_new_ic()
{
  XVaNestedList preedit_attr = NULL;
  XVaNestedList status_attr = NULL;
  static XFontSet fs = NULL;
  char *fnt;
  char **missing_list;
  int missing_count;
  char *def_string;
  static XRectangle spot;
  int predit = 0;
  int sarea = 0;
  XIMStyles* xim_styles = NULL;

#if USE_XFT

#if defined(__GNUC__)

#endif

  if (!fs) {
    fnt = (char*)"-misc-fixed-*";
    fs = XCreateFontSet(fl_display, fnt, &missing_list,
                        &missing_count, &def_string);
  }
#else
  if (!fs) {
    bool must_free_fnt = true;
    fnt = fl_get_font_xfld(0, 14);
    if (!fnt) {fnt = (char*)"-misc-fixed-*";must_free_fnt=false;}
    fs = XCreateFontSet(fl_display, fnt, &missing_list,
                        &missing_count, &def_string);
    if (must_free_fnt) free(fnt);
  }
#endif
  preedit_attr = XVaCreateNestedList(0,
                                     XNSpotLocation, &spot,
                                     XNFontSet, fs, NULL);
  status_attr = XVaCreateNestedList(0,
                                    XNAreaNeeded, &status_area,
                                    XNFontSet, fs, NULL);

  if (!XGetIMValues(fl_xim_im, XNQueryInputStyle,
                    &xim_styles, NULL, NULL)) {
    int i;
    XIMStyle *style;
    for (i = 0, style = xim_styles->supported_styles;
         i < xim_styles->count_styles; i++, style++) {
      if (*style == (XIMPreeditPosition | XIMStatusArea)) {
        sarea = 1;
        predit = 1;
      } else if (*style == (XIMPreeditPosition | XIMStatusNothing)) {
        predit = 1;
      }
    }
  }
  XFree(xim_styles);

  if (sarea) {
    fl_xim_ic = XCreateIC(fl_xim_im,
                          XNInputStyle, (XIMPreeditPosition | XIMStatusArea),
                          XNPreeditAttributes, preedit_attr,
                          XNStatusAttributes, status_attr,
                          NULL);
  }

  if (!fl_xim_ic && predit) {
    fl_xim_ic = XCreateIC(fl_xim_im,
                          XNInputStyle, (XIMPreeditPosition | XIMStatusNothing),
                          XNPreeditAttributes, preedit_attr,
                          NULL);
  }
  XFree(preedit_attr);
  XFree(status_attr);
  if (!fl_xim_ic) {
    fl_is_over_the_spot = 0;
    fl_xim_ic = XCreateIC(fl_xim_im,
                          XNInputStyle, (XIMPreeditNothing | XIMStatusNothing),
                          NULL);
  } else {
    fl_is_over_the_spot = 1;
    XVaNestedList status_attr = NULL;
    status_attr = XVaCreateNestedList(0, XNAreaNeeded, &status_area, NULL);

    XGetICValues(fl_xim_ic, XNStatusAttributes, status_attr, NULL);
    XFree(status_attr);
  }
}
