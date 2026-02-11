gdome_xmlGetChildrensLength (xmlNode *parent) {
  xmlNode *iter = NULL;
  gulong ret;

	for(iter = parent->children, ret = 0;
			iter != NULL;
			ret++,	iter = iter->next);

	return ret;
}
