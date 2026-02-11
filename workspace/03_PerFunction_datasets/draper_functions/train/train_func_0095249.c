getAskedNextCell() {

	int curCellRow = m_maze->getRowFromY(m_y);
	int curCellCol = m_maze->getColFromX(m_x);
	Cell nextCell;


	if (m_askedXSpeed > 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol + 1);
	} else if (m_askedXSpeed < 0) {
		nextCell = m_maze->getCell(curCellRow, curCellCol - 1);
	} else if (m_askedYSpeed > 0) {
		nextCell = m_maze->getCell(curCellRow + 1, curCellCol);
	} else if (m_askedYSpeed < 0) {
		nextCell = m_maze->getCell(curCellRow - 1, curCellCol);
	}

	return nextCell;
}
