font() const
{
  static QFont* f = 0;
  if (!f) f = new QFont(QApplication::font());

  return *f;
}
