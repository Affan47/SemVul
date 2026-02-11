appendConnectors(QList<ConnectorItem *> & connectorItems, ConnectorItem * connectorItem) {
	if (connectorItem == NULL) return;

	foreach (ConnectorItem * ci, connectorItem->connectedToItems()) {
		connectorItems.append(ci);
	}
}
