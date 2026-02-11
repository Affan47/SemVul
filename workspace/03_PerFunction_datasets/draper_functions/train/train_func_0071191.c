string_width (XlwMenuWidget mw, char *s)
{
  XCharStruct xcs;
  int drop;
#ifdef HAVE_XFT
  if (mw->menu.xft_font)
    {
      XGlyphInfo gi;
      XftTextExtentsUtf8 (XtDisplay (mw), mw->menu.xft_font,
                          (FcChar8 *) s,
                          strlen (s), &gi);
      return gi.width;
    }
#endif
#ifdef HAVE_X_I18N
  if (mw->menu.fontSet)
    {
      XRectangle ink, logical;
      XmbTextExtents (mw->menu.fontSet, s, strlen (s), &ink, &logical);
      return logical.width;
    }
#endif

  XTextExtents (mw->menu.font, s, strlen (s), &drop, &drop, &drop, &xcs);
  return xcs.width;

}
