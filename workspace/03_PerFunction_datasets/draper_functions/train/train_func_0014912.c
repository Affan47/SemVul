ParseNodes (xmlNodePtr node, bool writeable)
{
	gcp::Residue* r;
	while (node) {
		if (!strcmp ((char*) node->name, "residue")) {
			r = new gcp::Residue ();
			r->Load (node, !writeable, m_App);
		}
		node = node->next;
	}
}
