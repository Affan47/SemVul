getFeature(const XMLString& name) const
{
	if (name == FEATURE_FILTER_WHITESPACE)
		return _filterWhitespace;
	else
		return _saxParser.getFeature(name);
}
