resetCellSize()
{
	for(int i=0; i<rowCount(); ++i)
		setRowHeight(i, cellsize);
	for(int i=0; i<columnCount(); ++i)
		setColumnWidth(i, cellsize);
}
