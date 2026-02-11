collectWiresAux(QList<Wire *> & wires, ConnectorItem * start) {
	foreach (ConnectorItem * toConnectorItem, start->connectedToItems()) {
		if (toConnectorItem->attachedToItemType() == ModelPart::Wire) {
			qobject_cast<Wire *>(toConnectorItem->attachedTo())->collectWires(wires);
		}
	}

}
