CleanTree(rapidxml::xml_node<> *node) {
  if (node == NULL) { return; }

  for (rapidxml::xml_node<> *child = node->first_node(); child;) {
    rapidxml::xml_node<> *next_node = child->next_sibling();
    rapidxml::node_type type = child->type();
    std::string name = child->name();
    if (type == rapidxml::node_comment ||
        name == "script" || name == "style") {
      node->remove_node(child);
    } else {
      CleanTree(child);
    }
    child = next_node;
  }

  return;
}
