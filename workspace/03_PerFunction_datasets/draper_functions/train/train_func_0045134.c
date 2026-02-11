canLoad(QIODevice* file)
{
  if (!file) return false;

  Q_ASSERT(file->isOpen());


  char buf[2048];
  int read = file->read(buf,2047);
  if (read < 0)
	return false;
  buf[read] = 0;

  QByteArray s = QByteArray::fromRawData(buf, read+1);
  int pos = s.indexOf("events:");
  if (pos>0 && buf[pos-1] != '\n') pos = -1;
  return (pos>=0);
}
