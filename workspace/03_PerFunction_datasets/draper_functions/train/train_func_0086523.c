Save (xmlDocPtr xml) const
{
	if (m_RealSave && !const_cast <Fragment *> (this)->Validate ())
		return NULL;
	xmlNodePtr node = xmlNewDocNode (xml, NULL, (xmlChar*) "fragment", NULL);
	if (m_buf.length ()) {
		if (!m_Atom->GetBondsNumber () || m_Atom->GetZ ()) {
			if (!node)
				return NULL;
			if (!SavePortion (xml, node, 0, m_BeginAtom)) {
				xmlFreeNode (node);
				return NULL;
			}
			if (m_Atom->GetZ  ()) {
				xmlNodePtr child = m_Atom->Save(xml);
				if (!child) {
					xmlFreeNode(node);
					return NULL;
				}
				xmlAddChild(node, child);
			}
			if (!SavePortion(xml, node, m_EndAtom, m_buf.length ())) {
				xmlFreeNode(node);
				return NULL;
			}
		}
	}
	return (SaveNode (xml, node))? node: NULL;
}
