removeConnection(ConnectorItem * connectedItem, bool emitChange) {
	if (connectedItem == NULL) return;

	m_connectedTo.removeOne(connectedItem);
    QList<ConnectorItem *> visited;
	restoreColor(visited);
	if (emitChange) {
		m_attachedTo->connectionChange(this, connectedItem, false);
	}
}
