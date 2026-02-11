setColumnWidth(u32 columnIndex, u32 width)
{
	if ( columnIndex < Columns.size() )
	{
		const u32 MIN_WIDTH = Font->getDimension(Columns[columnIndex].Name.c_str() ).Width + (CellWidthPadding * 2);
		if ( width < MIN_WIDTH )
			width = MIN_WIDTH;

		Columns[columnIndex].Width = width;

		for ( u32 i=0; i < Rows.size(); ++i )
		{
			breakText( Rows[i].Items[columnIndex].Text, Rows[i].Items[columnIndex].BrokenText, Columns[columnIndex].Width );
		}
	}
	recalculateWidths();
}
