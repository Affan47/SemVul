operator<<(QDebug debug, const KDirWatchPrivate::Entry &entry)
{
  debug.nospace() << "[ Entry for " << entry.path << ", " << (entry.isDir ? "dir" : "file");
  if (entry.m_status == KDirWatchPrivate::NonExistent)
    debug << ", non-existent";
  debug << ", using " << ((entry.m_mode == KDirWatchPrivate::FAMMode) ? "FAM" :
                       (entry.m_mode == KDirWatchPrivate::INotifyMode) ? "INotify" :
                       (entry.m_mode == KDirWatchPrivate::DNotifyMode) ? "DNotify" :
                       (entry.m_mode == KDirWatchPrivate::QFSWatchMode) ? "QFSWatch" :
                       (entry.m_mode == KDirWatchPrivate::StatMode) ? "Stat" : "Unknown Method");
#ifdef HAVE_SYS_INOTIFY_H
  if (entry.m_mode == KDirWatchPrivate::INotifyMode)
    debug << " inotify_wd=" << entry.wd;
#endif
  debug << ", has " << entry.m_clients.count() << " clients";
  debug.space();
  if (!entry.m_entries.isEmpty()) {
    debug << ", nonexistent subentries:";
    Q_FOREACH(KDirWatchPrivate::Entry* subEntry, entry.m_entries)
      debug << subEntry << subEntry->path;
  }
  debug << ']';
  return debug;
}
