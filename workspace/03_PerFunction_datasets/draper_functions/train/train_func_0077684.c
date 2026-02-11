match(const Selector& s) const
{
	if (mElement.empty()) return false;

	if (s.mElement.empty())
	{
		Selector s2(s);
		s2.mElement = mElement;
		return *this == s2;
	}
	else
	{
		return *this == s;
	}
}
