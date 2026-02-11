LoadNode (xmlNodePtr node)
{
	char* buf;
	buf = (char*) xmlGetProp (node, (xmlChar*) "type");
	if (!buf)
		SetType (NormalBondType);
	else if (!strcmp (buf, "up"))
		SetType (UpBondType);
	else if (!strcmp (buf, "down"))
		SetType (DownBondType);
	else if (!strcmp (buf, "fore"))
		SetType (ForeBondType);
	else if (!strcmp (buf, "undetermined"))
		SetType (UndeterminedBondType);
	else if (!strcmp (buf, "newman"))
		SetType (NewmanBondType);
	else
		SetType (NormalBondType);
	if (buf)
		xmlFree (buf);
	buf = (char*) xmlGetProp (node, (xmlChar*) "level");
	if (buf) {
		m_level = atoi (buf);
		xmlFree (buf);
	}
	if (m_type == NewmanBondType)

		gcu::ReadFloat (node, "radius", m_coords[15], static_cast < Document * > (GetDocument ())->GetBondLength ());
	return true;
}
