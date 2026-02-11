mostBottomNode() {
	HourRangeNode *node = this;
	while (node->next())
		node = node->next();
	return node;
}
