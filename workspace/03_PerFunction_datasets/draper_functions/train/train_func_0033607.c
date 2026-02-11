isAuthorizedDesktopFile(const QString& path)
{
  if (path.isEmpty())
     return false;

  if (QDir::isRelativePath(path))
     return true;

  KStandardDirs *dirs = KGlobal::dirs();
  QStringList kdePrefixes;
  kdePrefixes += dirs->resourceDirs("apps");
  kdePrefixes += dirs->resourceDirs("services");
  kdePrefixes += dirs->resourceDirs("xdgdata-apps");
  kdePrefixes += dirs->resourceDirs("autostart");

  const QString realPath = KStandardDirs::realPath(path);


  foreach (const QString &prefix, kdePrefixes) {
#ifndef Q_OS_WIN
    if (realPath.startsWith(prefix))
#else
    if (realPath.startsWith(prefix, Qt::CaseInsensitive))
#endif
      return true;
  }


  if (!KAuthorized::authorize(QLatin1String("run_desktop_files"))) {
     kWarning() << "Access to '" << path << "' denied because of 'run_desktop_files' restriction." << endl;
     return false;
  }


  QFileInfo entryInfo( path );
  if (entryInfo.isExecutable() || entryInfo.ownerId() == 0)
      return true;

  kWarning() << "Access to '" << path << "' denied, not owned by root, executable flag not set." << endl;
  return false;
}
