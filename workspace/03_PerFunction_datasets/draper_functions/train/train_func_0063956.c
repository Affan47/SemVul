xml_create_data (xmlDocPtr   doc,
                 xmlNodePtr  parent,
		 xmlNsPtr    ns,
		 glLabel    *label)
{
	xmlNodePtr  node;
	GHashTable *cache;
	GList      *name_list, *p;

	gl_debug (DEBUG_XML, "START");

	node = xmlNewChild (parent, ns, (xmlChar *)"Data", NULL);

	cache = gl_label_get_pixbuf_cache (label);
	name_list = gl_pixbuf_cache_get_name_list (cache);

	for (p = name_list; p != NULL; p=p->next) {
		xml_create_pixdata (node, ns, label, p->data);
	}

	gl_pixbuf_cache_free_name_list (name_list);


	cache = gl_label_get_svg_cache (label);
	name_list = gl_svg_cache_get_name_list (cache);

	for (p = name_list; p != NULL; p=p->next) {
		xml_create_file_svg (doc, node, ns, label, p->data);
	}

	gl_pixbuf_cache_free_name_list (name_list);


	gl_debug (DEBUG_XML, "END");
}
