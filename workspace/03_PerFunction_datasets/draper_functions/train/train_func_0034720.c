deleteBusConnection() {
	WireAction * wireAction = qobject_cast<WireAction *>(sender());
	if (wireAction == NULL) return;

	Wire * wire = wireAction->wire();
	if (wire == NULL) return;

	QList<Wire *> wires;
	QList<ConnectorItem *> ends;
	wire->collectChained(wires, ends);
	if (ends.count() != 2) return;

	QString id0 = ends.at(0)->connectorSharedID();
	QString id1 = ends.at(1)->connectorSharedID();

	QDomElement root = m_fzpDocument.documentElement();
	QDomElement buses = root.firstChildElement("buses");
	QDomElement bus = buses.firstChildElement("bus");
	QDomElement nodeMember0;
	QDomElement nodeMember1;
	while (!bus.isNull()) {
		nodeMember0 = TextUtils::findElementWithAttribute(bus, "connectorId", id0);
		nodeMember1 = TextUtils::findElementWithAttribute(bus, "connectorId", id1);
		if (!nodeMember0.isNull() && !nodeMember1.isNull()) break;

		bus = bus.nextSiblingElement("bus");
	}

	QString busID = bus.attribute("id");

	if (nodeMember0.isNull() || nodeMember1.isNull()) {
		QMessageBox::critical(NULL, tr("Parts Editor"), tr("Internal connections are very messed up."));
		return;
	}

	QUndoCommand * parentCommand = new QUndoCommand();
	QStringList names;
	names << ends.at(0)->connectorSharedName() << ends.at(1)->connectorSharedName() ;
	new RemoveBusConnectorCommand(this, busID, id0, false, parentCommand);
	new RemoveBusConnectorCommand(this, busID, id1, false, parentCommand);
	if (ends.at(0)->connectedToItems().count() > 1) {

		names.removeAt(0);
		new RemoveBusConnectorCommand(this, busID, id0, true, parentCommand);
	}
	if (ends.at(1)->connectedToItems().count() > 1) {

		new RemoveBusConnectorCommand(this, busID, id1, true, parentCommand);
	}

	parentCommand->setText(tr("Remove internal connection from '%1'").arg(names.at(0)));
	m_undoStack->waitPush(parentCommand, SketchWidget::PropChangeDelay);
}
