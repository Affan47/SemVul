readProperties(const KConfigGroup& grp)
{
  kDebug() << "READ PROPERTIES for GROUP" << grp.name();

  QString filename = grp.readEntry("CurrentGame", QString());
  kDebug() << "Filename is" << filename;

  if(!filename.isNull() && QFile::exists(filename))
  {
    kDebug() << "Loading" << filename;

    kDebug() << "Loading" << filename << "done";
  }

}
