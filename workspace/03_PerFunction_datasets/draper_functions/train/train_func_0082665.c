locate()
{
	bool result;

	if (plist.empty())
		return false;

	std::map < string, field_value >::const_iterator i;
	first();
	while (!eof())
	{
		result = true;
		for (i = plist.begin(); i != plist.end(); ++i)
			if (fv(i->first.c_str()).get_asString() == i->second.get_asString())
			{
				continue;
			}
			else
			{
				result = false;
				break;
			}
		if (result)
		{
			return result;
		}
		next();
	}
	return false;
}
