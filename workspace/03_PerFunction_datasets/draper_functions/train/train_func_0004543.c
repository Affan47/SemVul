gsf_open_pkg_get_rels (GsfInput *opkg)
{
	GsfOpenPkgRels *rels = NULL;

	g_return_val_if_fail (opkg != NULL, NULL);

	if (NULL == (rels = g_object_get_data (G_OBJECT (opkg), "OpenPkgRels"))) {
		char const *part_name = gsf_input_name (opkg);
		GsfXMLInDoc *rel_doc;
		GsfInput *rel_stream;

		if (NULL != part_name) {
			GsfInfile *container = gsf_input_container (opkg);
			char *rel_name;

			g_return_val_if_fail (container != NULL, NULL);

			rel_name = g_strconcat (part_name, ".rels", NULL);
			rel_stream = gsf_infile_child_by_vname (container, "_rels", rel_name, NULL);
			g_free (rel_name);
		} else
			rel_stream = gsf_infile_child_by_vname (GSF_INFILE (opkg), "_rels", ".rels", NULL);

		if (NULL != rel_stream) {
			rels = g_new (GsfOpenPkgRels, 1);
			rels->by_id = g_hash_table_new_full (g_str_hash, g_str_equal,
				NULL, (GDestroyNotify)gsf_open_pkg_rel_free);
			rels->by_type = g_hash_table_new (g_str_hash, g_str_equal);

			rel_doc = gsf_xml_in_doc_new (open_pkg_rel_dtd, open_pkg_ns);
			(void) gsf_xml_in_doc_parse (rel_doc, rel_stream, rels);

			gsf_xml_in_doc_free (rel_doc);
			g_object_unref (rel_stream);
		}

		g_object_set_data_full (G_OBJECT (opkg), "OpenPkgRels", rels,
			(GDestroyNotify) gsf_open_pkg_rels_free);
	}

	return rels;
}
