addElementIndex(int size) {
	if (m_index != NULL) delete[] m_index;
	m_index = new TokLangElemPtr[size];
}
