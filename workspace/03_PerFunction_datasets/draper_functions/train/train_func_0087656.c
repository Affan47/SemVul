CountLinkChar(rapidxml::xml_document<> *doc,
                     rapidxml::xml_node<> *node) {
  if (doc == NULL || node == NULL) { return 0; }
  int link_char_num = 0;

  if (node->first_node() != NULL) {
    for (rapidxml::xml_node<> *child = node->first_node();
         child; child = child->next_sibling()) {
      link_char_num += CountLinkChar(doc, child);
    }

    std::string name = node->name();
    if (name == "a" || name == "input" || name == "button" || name == "option") {
      link_char_num = StrToInt(node->last_attribute(kCharNum)->value());
      UpdateLinkChar(doc, node);
    }

    int char_num = StrToInt(node->last_attribute(kCharNum)->value());
    if (link_char_num > char_num) {
      link_char_num = char_num;
    }
  }
  SetAttribute(kLinkCharNum, link_char_num, doc, node);

  return link_char_num;
}
