open()
{
	menu = new yesno_menu_t;
	menu->open();
	menu->select(1);
	return menu;
}
