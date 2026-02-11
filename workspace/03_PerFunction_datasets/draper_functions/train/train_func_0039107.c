namespaceDiscover(Address whereToDiscover, std::vector<std::string>& returnedNodes, std::vector<std::string>& returnedLeaves, std::vector<std::string>& returnedAttributes)
{
	if(m_discover_callback)
		m_discover_callback(m_discover_arguments , whereToDiscover, returnedNodes, returnedLeaves, returnedAttributes);
	else
		;
}
