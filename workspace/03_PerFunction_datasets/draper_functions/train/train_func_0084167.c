operator<<(std::ostream& os, const tool_path& path)
{
	for(tool_path::const_iterator s = path.begin(); s != path.end(); s++)
	{
		os << "{";
		for(segment::const_iterator v = (*s).begin(); v != (*s).end(); v++)
		{
			if(v != (*s).begin())
			{
				os << ", ";
			}
			os << (*v);
		}
		os << "}\n";
	}
	return os;
}
