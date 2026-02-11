loadSettings()
{
  QSettings s;
  restoreGeometry(s.value("ide/geometry").toByteArray());
}
