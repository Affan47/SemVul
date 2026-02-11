setZoom(int zoom)
{
  clear();

  QString strSelect;
  strSelect.sprintf("%d%%", zoom);

  bool inserted = false;
  for (unsigned int i = 0; i < sizeof(zoomDefaults) / sizeof(int); i++)
  {
    QString str;

    if (!inserted && (zoom > zoomDefaults [i]))
    {
      insertItem(strSelect);

      inserted = true;
    }
    else if (zoom == zoomDefaults [i])
      inserted = true;

    str.sprintf("%d%%", zoomDefaults [i]);
    insertItem(str);
  }

  setCurrentText(strSelect);
}
