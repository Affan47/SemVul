insert( const CRenderizablePtr &newObject, const std::string &viewportName )
{
	MRPT_START
	for (TListViewports::iterator it = m_viewports.begin();it!= m_viewports.end();++it)
	{
		if ((*it)->m_name == viewportName )
		{
			(*it)->insert(newObject);
			return;
		}
	}
	THROW_EXCEPTION_CUSTOM_MSG1("Error: viewport '%s' not found.",viewportName.c_str());
	MRPT_END
}
