setCellTrim(unsigned int row, unsigned int column, const char* data) {
	unsigned int idx = m_firstCell[row] + column;
	unsigned int size = std::min<unsigned int>(m_cellSize[idx], strlen(data));
	for (unsigned int i = 0; i < size; i++) {
		m_buffer[m_cellPos[idx] + i] = data[i];
	}
	m_cellSize[idx] = size;
}
