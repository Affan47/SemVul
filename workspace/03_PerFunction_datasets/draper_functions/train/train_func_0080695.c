write_scaled_path(std::ostream& os, const tool_path& path,
				float xstart, float ystart, float xscale, float yscale)
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
			write_scaled_lattice_point(os, *v, xstart, ystart, xscale, yscale);
		}
		os << "}\n";
	}
	return os;
}
