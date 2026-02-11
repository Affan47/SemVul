GetMode(w)
Widget w;
{
    CannaObject obj = (CannaObject)w;
    wchar *mode;
    static ICString icstr;

    icstr.nchars = obj->canna.ibuf->modelen;
    if (icstr.nchars > 0) {
      mode = obj->canna.ibuf->curmode;
      icstr.data = (char *)mode;
      icstr.nbytes = icstr.nchars * sizeof(wchar);
      icstr.attr = ICAttrNormalString;
    }
    return &icstr;
}
