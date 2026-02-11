Load (xmlNodePtr node)
{
	char* tmp, *endptr;
	bool result;
	tmp = (char*) xmlGetProp (node, (xmlChar*) "id");
	if (tmp) {
		SetId (tmp);
		xmlFree (tmp);
	}
	if (ReadPosition (node, NULL, &m_x, &m_y))
		return true;
	tmp = (char*) xmlGetProp(node, (xmlChar*) "x");
	if (!tmp)
		return false;
	m_x = strtod (tmp, &endptr);
	result = *endptr;
	xmlFree (tmp);
	if (result)
		return false;
	tmp = (char*) xmlGetProp (node, (xmlChar*) "y");
	if (!tmp)
		return false;
	m_y = strtod (tmp, &endptr);
	result = *endptr;
	xmlFree (tmp);
	if (result)
		return false;
	return true;
}
