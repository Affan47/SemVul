setCellType(const int p_row, const int p_column, const Cell::Type p_type) {
	if (p_row < 0 || p_row >= m_nbRows || p_column < 0 || p_column >= m_nbColumns) {
		kError() << "Bad maze coordinates";
	}
	m_cells[p_row][p_column].setType(p_type);
}
