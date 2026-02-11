run(int fn, IpeletData *data, IpeletHelper *helper)
{
  iData = data;
  QString name;
  if (fn != 2) {
    name = QFileDialog::getOpenFileName();
    if (name.isNull())
      return false;
  }
  switch (fn) {
  case 0:
    return insertBitmap(name);
  case 1:
    return insertJpeg(name);
  case 2:
    return insertBitmap(QString::null);
  default:
    return false;
  }
}
