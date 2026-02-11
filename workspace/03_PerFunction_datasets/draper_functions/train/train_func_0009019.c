setSelectForItemsInColumn(uint col_idx, bool state)
{
	for (uint i = 0; i < getRowCount(); ++i)
	{
		ListboxItem* item = d_grid[i][col_idx];

		if (item)
		{
			item->setSelected(state);
		}

	}

}
