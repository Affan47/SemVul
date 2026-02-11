WriteAtom (CDXMLLoader *loader, xmlDocPtr xml, xmlNodePtr parent, Object const *obj, G_GNUC_UNUSED GOIOContext *s)
{
	xmlNodePtr node = xmlNewDocNode (xml, NULL, reinterpret_cast <xmlChar const *> ("n"), NULL);
	xmlAddChild (parent, node);
	loader->m_SavedIds[obj->GetId ()] = loader->m_MaxId;
	AddIntProperty (node, "id", loader->m_MaxId++);
	string prop = obj->GetProperty (GCU_PROP_POS2D);
	AddStringProperty (node, "p", prop);
	AddIntProperty (node, "Z", loader->m_Z++);
	prop = obj->GetProperty (GCU_PROP_ATOM_Z);
	if (prop != "6")
		AddStringProperty (node, "Element", prop);
	return true;
}
