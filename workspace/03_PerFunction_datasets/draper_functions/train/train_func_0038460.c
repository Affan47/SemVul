findBabelVersion()
{
  QProcess babel;
  babel.start("gpsbabel", QStringList() << "-V");
  if (!babel.waitForStarted())
    return QString();
  babel.closeWriteChannel();
  if (!babel.waitForFinished())
    return QString();

  QString str = babel.readAll();
  is_beta = str.contains("-beta");
  str.replace("Version",  "");
  str.replace("GPSBabel",  "");
  str.replace(QRegExp("^[\\s]*"),  "");
  str.replace(QRegExp("[\\s]+$"),  "");
  str = str.simplified();
  return str;
}
