parse_rss_item(podcast_t * podcast, GSList ** list, xmlDocPtr doc, xmlNodePtr item) {

	podcast_item_t * pitem;
	xmlNodePtr node;

	if ((pitem = podcast_item_new()) == NULL) {
		return;
	}

	for (node = item->xmlChildrenNode; node != NULL; node = node->next) {
		if (!xmlStrcmp(node->name, (const xmlChar *)"title")) {
                        pitem->title = (char *)xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
		} else if (!xmlStrcmp(node->name, (const xmlChar *)"description")) {
                        pitem->desc = (char *)xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
		} else if (!xmlStrcmp(node->name, (const xmlChar *)"summary")) {
			if (pitem->desc == NULL) {
				pitem->desc = (char *)xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
			}
		} else if (!xmlStrcmp(node->name, (const xmlChar *)"enclosure")) {
			xmlChar * len;
			if ((len = xmlGetProp(node, (const xmlChar *)"length")) != NULL) {
				sscanf((char *)len, "%u", &pitem->size);
				xmlFree(len);
			}
			pitem->url = (char *)xmlGetProp(node, (const xmlChar *)"url");
		} else if (!xmlStrcmp(node->name, (const xmlChar *)"pubDate")) {
			xmlChar * tmp = xmlNodeListGetString(doc, node->xmlChildrenNode, 1);
			pitem->date = parse_rss_date((char *)tmp);
			xmlFree(tmp);
		}
	}

	if (pitem->url == NULL) {
		podcast_item_free(pitem);
		return;
	}

	string_remove_html(pitem->desc);

	if (pitem->title == NULL) {
		pitem->title = strdup(_("Untitled"));
	}

	if (g_slist_find_custom(*list, pitem->url, podcast_item_compare_url) == NULL) {
		*list = g_slist_prepend(*list, pitem);
	} else {
		podcast_item_free(pitem);
	}
}
