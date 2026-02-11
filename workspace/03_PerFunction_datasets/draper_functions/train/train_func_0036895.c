connectorItemHasSpec(ConnectorItem * connectorItem, ViewLayer::ViewLayerPlacement spec) {
	if (ViewLayer::specFromID(connectorItem->attachedToViewLayerID()) == spec)  return true;

	connectorItem = connectorItem->getCrossLayerConnectorItem();
	if (connectorItem == NULL) return false;

	return (ViewLayer::specFromID(connectorItem->attachedToViewLayerID()) == spec);
}
