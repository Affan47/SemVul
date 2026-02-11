get_pixmap(QString file_name)
{
  QPixmap * pm=new QPixmap(file_name);
  return *pm;
}
