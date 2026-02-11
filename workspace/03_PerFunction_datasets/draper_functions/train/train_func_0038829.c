factory( const QString &type )
{
  if (type == "netscape")
    return new KNSBookmarkImporterImpl;
  else if (type == "mozilla")
    return new KMozillaBookmarkImporterImpl;
  else if (type == "xbel")
    return new KXBELBookmarkImporterImpl;
  else if (type == "ie")
    return new KIEBookmarkImporterImpl;
  else if (type == "opera")
    return new KOperaBookmarkImporterImpl;
  else
    return 0;
}
