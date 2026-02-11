php_dom_remove_xinclude_nodes(xmlNodePtr cur TSRMLS_DC)
{
	while(cur) {
		if (cur->type == XML_XINCLUDE_START) {
			cur = php_dom_free_xinclude_node(cur TSRMLS_CC);


			while(cur && cur->type != XML_XINCLUDE_END) {

				if (cur->type == XML_ELEMENT_NODE) {
					   php_dom_remove_xinclude_nodes(cur->children TSRMLS_CC);
				}
				cur = cur->next;
			}

			if (cur && cur->type == XML_XINCLUDE_END) {
				cur = php_dom_free_xinclude_node(cur TSRMLS_CC);
			}
		} else {
			if (cur->type == XML_ELEMENT_NODE) {
				php_dom_remove_xinclude_nodes(cur->children TSRMLS_CC);
			}
			cur = cur->next;
		}
	}
}
