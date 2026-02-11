get_current_text() const
{
	int pos = 0;
	std::vector<CL_ListItem *>::const_iterator it;
	for(it = items.begin(); it != items.end(); ++it, ++pos)
		if((*it)->selected)
			return (*it)->str;

	return blank;
}
