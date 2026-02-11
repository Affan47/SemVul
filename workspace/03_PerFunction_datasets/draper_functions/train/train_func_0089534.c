visu_dump_png_getStatic()
{
  const gchar *typePng[] = {"*.png", (char*)0};

  if (png)
    return png;

  png = visu_dump_new(_("Png file"), typePng, writeViewInPngFormat, TRUE);

  waitFunc = (ToolVoidDataFunc)0;
  waitData = (gpointer)0;

  return png;
}
