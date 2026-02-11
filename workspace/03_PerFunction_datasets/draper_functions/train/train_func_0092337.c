upload(const QString& src, const KUrl& target, QWidget* window)
{
  if (target.isEmpty())
    return false;


  if (target.isLocalFile() && target.toLocalFile() == src)
    return true;

  NetAccess kioNet;
  KUrl s;
  s.setPath(src);
  return kioNet.filecopyInternal( s, target, -1, KIO::Overwrite, window, false  );
}
