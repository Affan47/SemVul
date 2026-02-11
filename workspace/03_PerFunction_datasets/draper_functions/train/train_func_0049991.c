set(
	const char *propertyName,
	const CSerializablePtr &obj,
	const int64_t &hypothesis_ID)
{
	MRPT_START

	for (std::vector<TPropertyValueIDTriplet>::iterator it=m_properties.begin();it!=m_properties.end();++it)
	{
		if ( it->ID == hypothesis_ID && !os::_strcmpi(propertyName,it->name.c_str()) )
		{


			it->value = obj;
			it->value.make_unique();


			return;
		}
	}


	TPropertyValueIDTriplet	newPair;
	newPair.name = std::string(propertyName);
	newPair.value = obj;
	newPair.ID    = hypothesis_ID;
	m_properties.push_back(newPair);

	MRPT_END_WITH_CLEAN_UP( \
		printf("Exception while setting annotation '%s'",propertyName); \
		);
}
