format(QString key)
{

  if (formats()->contains(key))
    return (*formats())[key];

  QTextCharFormat fmt = Private::defaultFormat(key);

  QSettings s;
  s.beginGroup("formats");
  s.beginGroup(key);
  if (s.contains("italic"))
    fmt.setFontItalic(s.value("italic").toBool());
  if (s.contains("weight")) {
    int i = s.value("weight").toInt();
    if ((i >= QFont::Light) && (i <= QFont::Black))
      fmt.setFontWeight(i);
  }
  if (s.contains("color")) {
    QColor c;
    c.setNamedColor(s.value("color").toString());
    if (c.isValid())
      fmt.setForeground(c);
  }
  if (s.contains("bgcolor")) {
    QColor c;
    c.setNamedColor(s.value("bgcolor").toString());
    if (c.isValid())
      fmt.setBackground(c);
  }

  (*formats())[key] = fmt;
  return fmt;
}
