has_mouse_over()
{
	if( menu->CL_Component::has_mouse_over() )
		return true;

	std::list<CL_MenuNode*>::iterator it;
	for( it = children.begin(); it != children.end(); ++it )
	{
		if( (*it)->has_mouse_over() )
			return true;
	}

	return false;
}
