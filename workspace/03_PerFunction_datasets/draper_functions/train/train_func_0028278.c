recoverBackupedFiles() {
	foreach(QString originalFilePath, m_filesReplacedByAlienOnes) {
		QFile file(m_tempDir.path()+"/"+QFileInfo(originalFilePath).fileName());
		if(file.exists(originalFilePath)) {
			file.remove();
		}
		FolderUtils::slamCopy(file, originalFilePath);
	}
	resetTempFolder();
}
