setSubMenu(u32 index, CGUIContextMenu* menu)
{
	if (index >= Items.size())
		return;

    if (menu)
        menu->grab();
	if (Items[index].SubMenu)
		Items[index].SubMenu->drop();

	Items[index].SubMenu = menu;
	menu->setVisible(false);

	if (Items[index].SubMenu)
	{
		menu->AllowFocus = false;
		if ( Environment->getFocus() == menu )
		{
			Environment->setFocus( this );
		}
	}

	recalculateSize();
}
