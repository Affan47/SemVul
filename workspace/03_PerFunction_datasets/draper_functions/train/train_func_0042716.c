set(const std::string &propertyName, const CSerializablePtr &obj)
{
	MRPT_START

	for (std::vector<TPropertyValuePair>::iterator it=m_properties.begin();it!=m_properties.end();++it)
	{
		if (!os::_strcmpi(propertyName.c_str(),it->name.c_str()))
		{


			if (!obj)	it->value.clear_unique();
			else		it->value = obj;
			return;
		}
	}


	TPropertyValuePair	newPair;
	newPair.name = std::string(propertyName);
	newPair.value = obj;
	m_properties.push_back(newPair);

	MRPT_END_WITH_CLEAN_UP( \
		printf("Exception while setting annotation '%s'",propertyName.c_str()); \
		);
}
