real_html_add_link_to_node (xmlNodePtr node, const gchar *text, const gchar *link_to)
{
	xmlNodePtr href;
	gchar *tmp;

	href = xmlNewNode (NULL, (xmlChar*)"a");
	tmp = g_strdup_printf (" [%s] ", text);
	xmlNodeSetContent (href, BAD_CAST tmp);
	g_free (tmp);
	if (node->children) {
		xmlNodePtr sibl;

		sibl = node->children;
		while (sibl && xmlNodeIsText (sibl))
			sibl = sibl->next;
		if (sibl)
			xmlAddPrevSibling (sibl, href);
		else
			xmlAddChild (node, href);
	}
	else
		xmlAddChild (node, href);
	if (*link_to == '/') {
		tmp = g_strdup_printf ("#%s", link_to);
		xmlSetProp(href, BAD_CAST "href", BAD_CAST tmp);
		g_free (tmp);
	}
	else
		xmlSetProp(href, BAD_CAST "href", BAD_CAST link_to);
}
