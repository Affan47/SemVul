on_reposition()
{
	CL_Rect menu_pos = node->get_parent_menu()->get_position();
	CL_Rect node_pos = node->get_position();
	CL_Menu *submenu = node->get_submenu();

	if( submenu )
	{
		if( node->get_parent_menu()->is_vertical() )
			submenu->reposition( menu_pos.right-2, menu_pos.top + node_pos.top+2 );
		else
		{
			submenu->reposition( menu_pos.left + node_pos.left, menu_pos.top+menu_pos.get_height() );
		}
	}
}
