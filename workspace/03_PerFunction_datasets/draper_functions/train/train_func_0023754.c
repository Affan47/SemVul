Load (xmlNodePtr node)
{
	char* buf;
	xmlNodePtr child;
	buf = reinterpret_cast <char *> (xmlGetProp (node, (xmlChar*) "id"));
	if (buf) {
		SetId (buf);
		xmlFree (buf);
	}
	child = GetNodeByName (node, "start");
	if (!child)
		return false;
	if (!ReadFloat (child, "x", m_x, 0.) || !ReadFloat (child, "y", m_y, 0.))
		return false;
	child = GetNodeByName (node, "end");
	if (!child)
		return false;
	if (!ReadFloat (child, "x", m_width, 0.) || !ReadFloat (child, "y", m_height, 0.))
		return false;
	m_width -= m_x;
	m_height -= m_y;
	GetDocument ()->ObjectLoaded (this);
	return true;
}
