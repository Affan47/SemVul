htmlize(MathData const & dat, HtmlStream & os)
{
	MathData ar = dat;
	extractStructure(ar, HTML);
	if (ar.size() == 0)
		return;
	if (ar.size() == 1) {
		os << ar.front();
		return;
	}
	for (MathData::const_iterator it = ar.begin(); it != ar.end(); ++it)
		(*it)->htmlize(os);
}
