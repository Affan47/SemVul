doWriteSymLink(const QString &name, const QString &target,
                          const QString &user, const QString &group,
                          mode_t perm, time_t atime, time_t mtime, time_t ctime) {


  perm |= S_IFLNK;
  Compression c = compression();
  setCompression(NoCompression);

  if (!doPrepareWriting(name, user, group, 0, perm, atime, mtime, ctime)) {
    kWarning() << "prepareWriting failed";
    setCompression(c);
    return false;
  }

  QByteArray symlink_target = QFile::encodeName(target);
  if (!writeData(symlink_target, symlink_target.length())) {
    kWarning() << "writeData failed";
    setCompression(c);
    return false;
  }

  if (!finishWriting(symlink_target.length())) {
    kWarning() << "finishWriting failed";
    setCompression(c);
    return false;
  }

  setCompression(c);
  return true;
}
