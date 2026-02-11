viewConnectorItemInfo(QGraphicsSceneHoverEvent *, ConnectorItem * connectorItem) {

	int count = connectorItem ? connectorItem->connectionsCount() : 0;
	if (m_lastConnectorItem == connectorItem && m_lastConnectorItemCount == count) return;

	m_lastConnectorItem = connectorItem;
	m_lastConnectorItemCount = count;

	Connector * connector = NULL;
	if (connectorItem) {
		if (connectorItem->attachedTo() != m_lastItemBase) {
			return;
		}

		connector = connectorItem->connector();
	}

	if (m_connDescr) {
		m_connDescr->setText(connectorItem ? tr("connected to %n item(s)", "", connectorItem->connectionsCount()) : "");
		m_connName->setText(connector ? connector->connectorSharedName() : "");
		m_connType->setText(connector ? Connector::connectorNameFromType(connector->connectorType()) : "");
	}

}
