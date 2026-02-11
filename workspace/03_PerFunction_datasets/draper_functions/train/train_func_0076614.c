hasNonConnectors() {
	foreach (QGraphicsItem * childItem, childItems()) {
		if (dynamic_cast<NonConnectorItem *>(childItem) != NULL) return true;
	}

	return false;
}
