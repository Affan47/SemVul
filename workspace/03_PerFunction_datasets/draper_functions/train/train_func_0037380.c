hasFeature(const XMLString& feature, const XMLString& version) const
{
	XMLString lcFeature = Poco::toLower(feature);
	return (lcFeature == FEATURE_XML && version == VERSION_1_0) ||
	       (lcFeature == FEATURE_CORE && version == VERSION_2_0) ||
	       (lcFeature == FEATURE_EVENTS && version == VERSION_2_0) ||
	       (lcFeature == FEATURE_MUTATIONEVENTS && version == VERSION_2_0) ||
	       (lcFeature == FEATURE_TRAVERSAL && version == VERSION_2_0);
}
