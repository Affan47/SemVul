atlasWindow()
{
  if(!_atlasWindow)
  {
    _atlasWindow = new CSVAtlasWindow(this);
    connect(_atlasWindow, SIGNAL(delimiterChanged(QString)), _delim, SLOT(setEditText(QString)));
  }
  return _atlasWindow;
}
