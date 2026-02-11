tracker_ontologies_shutdown (void)
{
	if (!initialized) {
		return;
	}

	g_ptr_array_foreach (namespaces, (GFunc) g_object_unref, NULL);
	g_ptr_array_free (namespaces, TRUE);

	g_hash_table_unref (namespace_uris);
	namespace_uris = NULL;

	g_ptr_array_foreach (ontologies, (GFunc) g_object_unref, NULL);
	g_ptr_array_free (ontologies, TRUE);

	g_hash_table_unref (ontology_uris);
	ontology_uris = NULL;

	g_ptr_array_foreach (classes, (GFunc) g_object_unref, NULL);
	g_ptr_array_free (classes, TRUE);

	g_hash_table_unref (class_uris);
	class_uris = NULL;

	g_hash_table_unref (id_uri_pairs);
	id_uri_pairs = NULL;

	g_ptr_array_foreach (properties, (GFunc) g_object_unref, NULL);
	g_ptr_array_free (properties, TRUE);

	g_hash_table_unref (property_uris);
	property_uris = NULL;

	g_type_class_unref (property_type_enum_class);
	property_type_enum_class = NULL;

	if (rdf_type) {
		g_object_unref (rdf_type);
		rdf_type = NULL;
	}

	if (gvdb_table) {
		gvdb_table_unref (gvdb_properties_table);
		gvdb_properties_table = NULL;

		gvdb_table_unref (gvdb_classes_table);
		gvdb_classes_table = NULL;

		gvdb_table_unref (gvdb_namespaces_table);
		gvdb_namespaces_table = NULL;

		gvdb_table_unref (gvdb_table);
		gvdb_table = NULL;
	}

	initialized = FALSE;
}
