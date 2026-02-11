collectEqualPotential(QList<ConnectorItem *> & connectorItems, bool crossLayers, ViewGeometry::WireFlags skipFlags) {


	QList<ConnectorItem *> tempItems = connectorItems;
	connectorItems.clear();

	for (int i = 0; i < tempItems.count(); i++) {
		ConnectorItem * connectorItem = tempItems[i];


		Wire * fromWire = (connectorItem->attachedToItemType() == ModelPart::Wire) ? qobject_cast<Wire *>(connectorItem->attachedTo()) : NULL;
		if (fromWire != NULL) {
			if (fromWire->hasAnyFlag(skipFlags)) {

				continue;
			}
		}
		else {
			if (crossLayers) {
				ConnectorItem * crossConnectorItem = connectorItem->getCrossLayerConnectorItem();
				if (crossConnectorItem != NULL) {
					if (!tempItems.contains(crossConnectorItem)) {
						tempItems.append(crossConnectorItem);
					}
				}
			}
		}


		connectorItems.append(connectorItem);


		foreach (ConnectorItem * cto, connectorItem->connectedToItems()) {
			if (tempItems.contains(cto)) continue;

			if ((skipFlags & ViewGeometry::NormalFlag) && (fromWire == NULL) && (cto->attachedToItemType() != ModelPart::Wire)) {

				continue;
			}

			tempItems.append(cto);
		}

		Bus * bus = connectorItem->bus();
		if (bus != NULL) {
			QList<ConnectorItem *> busConnectedItems;
			connectorItem->attachedTo()->busConnectorItems(bus, connectorItem, busConnectedItems);
#ifndef QT_NO_DEBUG
			if (connectorItem->attachedToItemType() == ModelPart::Wire && busConnectedItems.count() != 2) {
				connectorItem->debugInfo("bus is missing");


			}
#endif
			foreach (ConnectorItem * busConnectedItem, busConnectedItems) {
				if (!tempItems.contains(busConnectedItem)) {
					tempItems.append(busConnectedItem);
				}
			}
		}
	}
}
