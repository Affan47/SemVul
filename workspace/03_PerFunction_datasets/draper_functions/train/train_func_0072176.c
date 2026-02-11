databaseChanged(const QString &path)
{
    if (m_manager->m_userDb && path == m_manager->m_userDb->databasePath())
        notifyChanges(m_manager->m_userDb, DatabaseManager::UserScope);
    else if (path == m_manager->m_systemDb->databasePath())
        notifyChanges(m_manager->m_systemDb, DatabaseManager::SystemScope);


    if (!m_watcher->files().contains(path) && QFile::exists(path))
        m_watcher->addPath(path);
}
