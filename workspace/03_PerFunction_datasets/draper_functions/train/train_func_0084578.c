updateMenu() {


		enableProgramButton();


		emit programWindowUpdateRequest(m_programButton ? m_programButton->isEnabled() : false, m_canUndo, m_canRedo, m_canCut, m_canCopy,
			m_language, m_port, m_programmerPath.isEmpty() ? ProgramWindow::LocateName : m_programmerPath, m_filename);
}
