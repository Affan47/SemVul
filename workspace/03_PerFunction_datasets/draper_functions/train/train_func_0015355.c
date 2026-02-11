midgard_replicator_import_from_xml (MidgardConnection *mgd,  const gchar *xml, gboolean force)
{
	g_return_if_fail (mgd != NULL);
	g_return_if_fail (xml != NULL);

	xmlDoc *doc = NULL;
	xmlNode *root_node = NULL;
	midgard_core_object_get_xml_doc(mgd, xml, &doc, &root_node);

	if(doc == NULL || root_node == NULL)
		return;

	xmlNodePtr child = _get_type_node(root_node->children);
	if(!child) {
		g_warning("Can not get midgard type name from the given xml");
		xmlFreeDoc(doc);
		return;
	}

	GType object_type = g_type_from_name((const gchar *)child->name);

	if(object_type == MIDGARD_TYPE_BLOB) {

		__import_blob_from_xml(mgd, doc, child);
		return;
	}

	xmlChar *attr, *guid_attr;
	MidgardObject *dbobject;

	for(; child; child = _get_type_node(child->next)) {

		attr = xmlGetProp(child, BAD_CAST "purge");
		guid_attr = xmlGetProp(child, BAD_CAST "guid");

		if(attr && g_str_equal(attr, "yes")) {

			dbobject = midgard_schema_object_factory_get_object_by_guid (mgd, (const gchar *)guid_attr);

			if(dbobject ||
					( !dbobject &&
					 (mgd->errnum == MGD_ERR_OBJECT_DELETED)
					 )) {

				midgard_object_purge(dbobject, FALSE);
				if(dbobject)
					g_object_unref(dbobject);
				xmlFree(attr);
				xmlFree(guid_attr);
				continue;
			}
		}

		xmlFree(attr);

		MidgardObject *object =
			midgard_object_new(mgd, (const gchar *)child->name, NULL);
		if(!object) {
			g_warning("Can not create %s instance", child->name);
			xmlFreeDoc(doc);
			xmlFree(attr);
			xmlFree(guid_attr);
			continue;
		}

		if (guid_attr) {
			MGD_OBJECT_GUID (object) = (const gchar *)g_strdup((gchar *)guid_attr);
		}

		if(!_nodes2object(G_OBJECT(object), child->children, force)) {
			xmlFree(guid_attr);
			g_object_unref(object);
			continue;
		}

		if (!midgard_replicator_import_object (MIDGARD_DBOBJECT (object), force)) {

			xmlFree (guid_attr);
			g_object_unref (object);
			continue;

		} else {

			xmlFree (guid_attr);
			g_object_unref (object);
		}
	}

	xmlFreeDoc (doc);
}
