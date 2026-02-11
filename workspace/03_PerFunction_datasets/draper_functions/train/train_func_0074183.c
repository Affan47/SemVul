doOpen()
{
  QString m = tr("Open File");
  QString d = QDir::currentPath();
  QString f = fileDialogFilters();
  QString s = allFilesFilter();
  QFileDialog::Options o = QFileDialog::DontUseNativeDialog;
  QStringList files = QFileDialog::getOpenFileNames(window(), m, d, f, &s, o);
  foreach(QString fname, files)
    if (! fname.isEmpty())
      doOpenFile(fname);
}
