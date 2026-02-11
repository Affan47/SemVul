Save (xmlDocPtr xml) const
{
	xmlNodePtr node = FragmentAtom::Save (xml);
	if (node) {
		xmlNodeSetName (node, (xmlChar const *) "residue");
		static_cast <Document *> (GetFragment ()->GetDocument ())->SaveResidue (m_Residue, node);
	}
	return node;
}
