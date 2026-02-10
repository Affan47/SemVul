get_selected_items() const
{
	std::vector<std::string> retval;
	std::vector<CL_ListItem *>::const_iterator it;

	for(it = items.begin(); it != items.end(); ++it)
		if((*it)->selected)
			retval.push_back((*it)->str);

	return retval;
}
