undoStackCleanChanged(bool isClean) {
	if(!isClean && currentBinIsCore()) {
		setFilename(QString::null);
	}
	setWindowModified(!isClean);
	m_manager->setDirtyTab(this,isClean);
}
