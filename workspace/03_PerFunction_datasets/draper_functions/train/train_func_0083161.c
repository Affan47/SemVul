get_menu( std::vector<std::string> path )
{
	bool final_step = false;
	std::string wanted = path.front();

	path.erase(path.begin());
	if( path.empty() )
		final_step = true;

	std::list<CL_MenuNode*>::iterator it;
	for( it = children.begin(); it != children.end(); ++it )
	{
		CL_MenuNode *node = (*it);

		if( node->has_submenu() )
		{
			if( node->get_name() == wanted )
			{
				if( final_step )
					return node->get_submenu();
				else
					return node->get_submenu()->impl->get_menu(path);
			}
		}
	}

	return 0;
}
