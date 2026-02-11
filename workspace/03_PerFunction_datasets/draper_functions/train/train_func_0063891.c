mostLocalUrl(const KUrl & url, QWidget* window)
{
  if ( url.isLocalFile() )
  {
    return url;
  }

  KIO::UDSEntry entry;
  if (!stat(url, entry, window))
  {
    return url;
  }

  const QString path = entry.stringValue( KIO::UDSEntry::UDS_LOCAL_PATH );
  if ( !path.isEmpty() )
  {
    KUrl new_url;
    new_url.setPath(path);
    return new_url;
  }

  return url;
}
