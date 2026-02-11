insertInclude(int offs, GLESourceFile* file) {
	m_Files.push_back(file);
	if (file->getNbLines() > 0) {
		m_Code.insert(m_Code.begin()+offs+1, file->getNbLines()-1, (GLESourceLine*)NULL);
		for (int i = 0; i < file->getNbLines(); i++) {
			m_Code[offs+i] = file->getLine(i);
		}
		reNumber();
	}
}
