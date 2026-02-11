on_mouse_down(const CL_InputEvent &e)
{
	if( !parent_menu->is_vertical() )
		parent_menu->set_click_to_open(false);


	if( !node->get_parent_menu()->is_vertical() )
	{
		if( node->is_enabled(false) && submenu != 0 )
		{
			if( !submenu->is_open() )
			{
				open_submenu();
				close_lock = true;
			}
		}
	}
}
