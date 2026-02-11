notify_element_declaration(ElementT *e, const char *pos1, const char *pos2, const char *decl_pos2) {
	add_item(pos1, "<a name='" + link_element_decl(e) + "'>", pos2, "</a>");
	add_item(pos1, "<span class='c-ed'>", decl_pos2, "</span>");
	notify_element_reference(e, pos1, decl_pos2);
    }
