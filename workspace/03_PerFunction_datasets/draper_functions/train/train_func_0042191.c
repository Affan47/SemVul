setCellText(u32 rowIndex, u32 columnIndex, const core::stringw& text, video::SColor color)
{
	if ( rowIndex < Rows.size() && columnIndex < Columns.size() )
	{
		Rows[rowIndex].Items[columnIndex].Text = text;
		breakText( Rows[rowIndex].Items[columnIndex].Text, Rows[rowIndex].Items[columnIndex].BrokenText, Columns[columnIndex].Width );
		Rows[rowIndex].Items[columnIndex].Color = color;
		Rows[rowIndex].Items[columnIndex].IsOverrideColor = true;
	}
}
