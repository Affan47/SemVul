operator<(const CapsSpec& s) const
{
	return (node() != s.node() ? node() < s.node() :
			(version() != s.version() ? version() < s.version() :
			 extensions() < s.extensions()));
}
