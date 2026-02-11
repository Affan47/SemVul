possibleFolders() {
	if (m_possibleFolders.count() == 0) {
		m_possibleFolders << "core" << "obsolete" << "contrib" << "user";
	}

	return m_possibleFolders;
}
