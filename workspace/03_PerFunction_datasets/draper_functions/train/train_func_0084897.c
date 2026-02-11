displayRatsnest(QList<ConnectorItem *> & partConnectorItems, ViewGeometry::WireFlags myFlag) {
	bool formerColorWasNamed = false;
	bool gotFormerColor = false;
	QColor formerColor;

	VirtualWire * vw = NULL;
	foreach (ConnectorItem * fromConnectorItem, partConnectorItems) {
		foreach (ConnectorItem * toConnectorItem, fromConnectorItem->connectedToItems()) {
			vw = qobject_cast<VirtualWire *>(toConnectorItem->attachedTo());
			if (vw != NULL) break;
		}
		if (vw != NULL) break;
	}

	if (vw != NULL) {
		formerColorWasNamed = vw->colorWasNamed();
		formerColor = vw->color();
		gotFormerColor = true;
		clearRatsnestDisplay(partConnectorItems);
	}

	InfoGraphicsView * infoGraphicsView = InfoGraphicsView::getInfoGraphicsView(this);
	if (infoGraphicsView == NULL) return;

	if (partConnectorItems.count() < 2) return;

	QStringList connectorNames;
	ConnectorItem::collectConnectorNames(partConnectorItems, connectorNames);
	QColor color;
	bool colorWasNamed = RatsnestColors::findConnectorColor(connectorNames, color);
	if (!colorWasNamed) {
		if (!formerColorWasNamed && gotFormerColor) {
			color = formerColor;
		}
		else {
			infoGraphicsView->getRatsnestColor(color);
		}
	}

	ConnectorPairHash result;
	GraphUtils::chooseRatsnestGraph(&partConnectorItems, (ViewGeometry::RatsnestFlag | ViewGeometry::NormalFlag | ViewGeometry::PCBTraceFlag | ViewGeometry::SchematicTraceFlag) ^ myFlag, result);

	foreach (ConnectorItem * key, result.uniqueKeys()) {
		foreach (ConnectorItem * value, result.values(key)) {
			VirtualWire * vw = infoGraphicsView->makeOneRatsnestWire(key, value, false, color, false);
			if (vw) {
				vw->setColorWasNamed(colorWasNamed);
			}
		}
	}
}
