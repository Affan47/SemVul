filenameOnly(const QString& path)
{
   int i = path.lastIndexOf(QRegExp(QLatin1String("[/\\]")));
   if (i >= 0)
      return path.mid(i+1);
   return path;
}
