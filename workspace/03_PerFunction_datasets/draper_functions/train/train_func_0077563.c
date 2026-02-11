on_paint()
{
	if( menu_item->is_toggling() )
	{
		if( sur_checked == 0 && sur_unchecked == 0 )
		{
			if (resources->exists("MenuItem/checked"))
				sur_checked = new CL_Surface("MenuItem/checked", resources);
			if (resources->exists("MenuItem/unchecked"))
				sur_unchecked = new CL_Surface("MenuItem/unchecked", resources);
		}

		if( menu_item->is_selected() )
		{
			if( sur_checked )
				sur_checked->draw(menu_item->get_screen_x(),menu_item->get_screen_y());
		}
		else
		{
			if( sur_unchecked )
				sur_unchecked->draw(menu_item->get_screen_x(),menu_item->get_screen_y());
		}
	}
	else if( sur_icon )
		sur_icon->draw(menu_item->get_screen_x(),menu_item->get_screen_y());

	const char *text = menu_item->get_text().c_str();


	bool is_enabled = menu_item->get_parent()->is_enabled();


	if( menu_item->get_parent()->get_parent()->is_enabled() == false )
		is_enabled = false;

	if( menu_item->use_icon() )
	{
		if( is_enabled )
			font->draw(menu_item->get_screen_x()+20, menu_item->get_screen_y()+2, text);
		else
			font_disabled->draw(menu_item->get_screen_x()+18, menu_item->get_screen_y()+2, text);
	}
	else
	{
		if( is_enabled )
			font->draw(menu_item->get_screen_x()+2, menu_item->get_screen_y()+2, text);
		else
			font_disabled->draw(menu_item->get_screen_x()+2, menu_item->get_screen_y()+2, text);
	}
}
