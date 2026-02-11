setAtlasMap(const QString mapname)
{
  if (_csvtoolwindow && _csvtoolwindow->atlasWindow())
    return _csvtoolwindow->atlasWindow()->setMap(mapname);

  return false;
}
