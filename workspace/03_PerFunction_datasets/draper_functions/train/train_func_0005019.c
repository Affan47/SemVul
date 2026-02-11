linkFiles(const QList<LinkedFile *> & linkedFiles, const QString & alternativePath) {
    if (linkedFiles.isEmpty()) return;

    bool firstTime = true;
    foreach (LinkedFile * linkedFile, linkedFiles) {
        ProgramTab * programTab = NULL;
        if (firstTime) {
            firstTime = false;
            programTab = indexWidget(0);
        }
        else {
            programTab = addTab();
        }
        QDir dir(alternativePath);
        QFileInfo fileInfo(linkedFile->linkedFilename);
        programTab->loadProgramFile(linkedFile->linkedFilename, dir.absoluteFilePath(fileInfo.fileName()), false);
		if ((linkedFile->fileFlags & LinkedFile::InBundleFlag) && ((linkedFile->fileFlags & LinkedFile::ReadOnlyFlag) == 0)) {
			if (linkedFile->fileFlags & LinkedFile::SameMachineFlag) {
				programTab->appendToConsole(tr("File '%1' was restored from the .fzz file; the local copy was not found.").arg(fileInfo.fileName()));
			}
			else {
				programTab->appendToConsole(tr("File '%1' was restored from the .fzz file; save a local copy to work with an external editor.").arg(fileInfo.fileName()));
			}
		}
		if (!m_languages.value(linkedFile->language, "").isEmpty()) {
			programTab->setLanguage(linkedFile->language, false);
		}
		else {
			linkedFile->language.clear();
		}
		if (programTab->setProgrammer(linkedFile->programmer)) {
			linkedFile->programmer.clear();
		}
    }
}
