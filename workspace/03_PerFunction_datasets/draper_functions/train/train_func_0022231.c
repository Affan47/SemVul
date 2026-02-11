build_store_save(build_store_t * data) {

	xmlDocPtr doc;
	xmlNodePtr root;
	xmlNodePtr node;

	doc = xmlParseFile(data->file);
        root = xmlDocGetRootElement(doc);

	for (node = root->xmlChildrenNode; node != NULL; node = node->next) {

		if (!xmlStrcmp(node->name, (const xmlChar *)"builder")) {
			xmlUnlinkNode(node);
			xmlFreeNode(node);
			break;
		}
	}

	node = xmlNewTextChild(root, NULL, (const xmlChar *)"builder", NULL);

	xml_save_int(node, "type", data->type);
	xml_save_str(node, "root", data->root);
	xml_save_int(node, "artist_dir_depth", data->artist_dir_depth);
	xml_save_int(node, "excl_enabled", data->excl_enabled);
	xml_save_str(node, "excl_pattern", data->excl_pattern);
	xml_save_int(node, "incl_enabled", data->incl_enabled);
	xml_save_str(node, "incl_pattern", data->incl_pattern);
	xml_save_int(node, "reset_existing_data", data->reset_existing_data);
	xml_save_int(node, "remove_dead_files", data->remove_dead_files);

	xml_save_int(node, "artist_sort_by", data->artist_sort_by);
	xml_save_int(node, "record_sort_by", data->record_sort_by);
	xml_save_int(node, "rec_add_year_to_comment", data->rec_add_year_to_comment);
	xml_save_int(node, "trk_rva_enabled", data->trk_rva_enabled);
	xml_save_int(node, "trk_comment_enabled", data->trk_comment_enabled);

	data_src_save(node, "data_src_artist", data->data_src_artist);
	data_src_save(node, "data_src_record", data->data_src_record);
	data_src_save(node, "data_src_track", data->data_src_track);

	capitalize_save(node, "capitalize_artist", data->capitalize_artist);
	capitalize_save(node, "capitalize_record", data->capitalize_record);
	capitalize_save(node, "capitalize_track", data->capitalize_track);

	file_transform_save(node, "file_transform_artist", data->file_transform_artist);
	file_transform_save(node, "file_transform_record", data->file_transform_record);
	file_transform_save(node, "file_transform_track", data->file_transform_track);

        xmlSaveFormatFile(data->file, doc, 1);
	xmlFreeDoc(doc);
}
