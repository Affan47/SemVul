gdome_xmlAppendChild(xmlNode *parent, xmlNode* child) {
  xmlNode *iter;

  if (parent == NULL || child == NULL)
		return NULL;

  if (child->type == XML_DOCUMENT_FRAG_NODE) {
		if (child->children != NULL && child->last != NULL) {
      for (iter = child->children; iter != NULL; iter = iter->next)
        iter->parent = parent;

      if (parent->last) {
        parent->last->next = child->children;
        child->children->prev = parent->last;
      } else {
        parent->children = child->children;
        child->children->prev = NULL;
      }
      parent->last = child->last;
      child->last->next = NULL;
    }
  } else {
    if (parent->last) {
      parent->last->next = child;
      child->prev = parent->last;
    } else {
      parent->children = child;
      child->prev = NULL;
    }
    parent->last = child;
    child->next = NULL;
    child->parent = parent;
  }

	return child;
}
