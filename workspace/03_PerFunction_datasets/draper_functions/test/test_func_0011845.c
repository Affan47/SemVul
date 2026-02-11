removeItem(u32 idx)
{
	if (idx >= Items.size())
		return;

	if (Items[idx].SubMenu)
	{
		Items[idx].SubMenu->drop();
		Items[idx].SubMenu = 0;
	}

	Items.erase(idx);
	recalculateSize();
}
