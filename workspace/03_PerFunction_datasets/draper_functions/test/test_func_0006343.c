setFirstLineHeader(bool isheader)
{
  if (DEBUG) qDebug("CSVImpPlugin::setFirstLineHeader(%d)", isheader);
  _firstLineIsHeader = isheader;
  if (_csvtoolwindow)
    _csvtoolwindow->sFirstRowHeader(isheader);

  return true;
}
