removeAllItems()
{
	for (u32 i=0; i<Items.size(); ++i)
		if (Items[i].SubMenu)
			Items[i].SubMenu->drop();

	Items.clear();
	recalculateSize();
}
