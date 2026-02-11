insertRow(ListboxItem* item, uint col_id, uint row_idx, uint row_id)
{

	if (getSortDirection() != ListHeaderSegment::None)
	{
		return addRow(item, col_id, row_id);
	}
	else
	{

		ListRow row;
		row.d_sortColumn = getSortColumn();
		row.d_items.resize(getColumnCount(), 0);
		row.d_rowID = row_id;


		if (row_idx > getRowCount())
		{
			row_idx = getRowCount();
		}

		d_grid.insert(d_grid.begin() + row_idx, row);


		setItem(item, col_id, row_idx);


		WindowEventArgs args(this);
		onListContentsChanged(args);

		return row_idx;
	}

}
