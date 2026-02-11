handle_button(PG_Button* button, PG_Pointer last) {
	MenuBarItem* item = static_cast<MenuBarItem*>(last);


	if(item->popupmenu->IsVisible()) {
		item->popupmenu->Hide();
		my_active = NULL;
		return true;
	}

	if(my_active != NULL) {
		my_active->Hide();
		my_active = NULL;
	}

	my_active = item->popupmenu;
	my_active->openMenu(button->x, button->y + button->h);

	return true;
}
