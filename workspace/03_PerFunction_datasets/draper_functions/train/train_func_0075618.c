tempRemoveAllConnections() {
	ConnectorItem * connectorItem = connector0();
	for (int j = connectorItem->connectedToItems().count() - 1; j >= 0; j--) {
		connectorItem->connectedToItems()[j]->tempRemove(connectorItem, false);
		connectorItem->tempRemove(connectorItem->connectedToItems()[j], false);
	}
	connectorItem = connector1();
	for (int j = connectorItem->connectedToItems().count() - 1; j >= 0; j--) {
		connectorItem->connectedToItems()[j]->tempRemove(connectorItem, false);
		connectorItem->tempRemove(connectorItem->connectedToItems()[j], false);
	}
}
