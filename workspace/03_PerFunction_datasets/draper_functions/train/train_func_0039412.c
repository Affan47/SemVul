IsMember(const std::string &item,
			const std::vector<std::string> &types)
{
	std::vector<std::string>::const_iterator i = types.begin();
	for( ; i != types.end(); ++i ) {
		if( strcasecmp(i->c_str(), item.c_str()) == 0 )
			return true;
	}
	return false;
}

}
