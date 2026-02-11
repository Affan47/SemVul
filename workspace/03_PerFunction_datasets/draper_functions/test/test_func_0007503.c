prepSave(ProgramTab * programTab, bool saveAsFlag)
{
	m_savingProgramTab = programTab;

	bool result = (saveAsFlag)
		? saveAs(programTab->filename(), programTab->readOnly())
		: save(programTab->filename(), programTab->readOnly());

    if (result) {
		programTab->setClean();
		emit linkToProgramFile(programTab->filename(), programTab->language(), programTab->programmer(), true, true);
	}
	return result;
}
