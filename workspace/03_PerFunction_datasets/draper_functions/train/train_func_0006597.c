removePart(const QString & moduleID, const QString & path) {
	m_iconView->removePart(moduleID);
	m_listView->removePart(moduleID);


	m_model->removePart(moduleID);
    if (path.contains(FolderUtils::getUserDataStorePath())) {
        m_removed << path;
    }
}
