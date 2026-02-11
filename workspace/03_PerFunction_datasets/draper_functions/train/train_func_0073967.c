appendWireStuff(Wire* wire, bool swappingEnabled) {
	if (wire == NULL) return;

	ModelPart *modelPart = wire->modelPart();
	if (modelPart == NULL) return;
	if (modelPart->modelPartShared() == NULL) return;

	QString autoroutable = wire->getAutoroutable() ? tr("(autoroutable)") : "";
	QString nameString = tr("Wire");
	if (swappingEnabled) {
		if (wire->getRatsnest()) {
			nameString = tr("Ratsnest wire");
		}
		else if(wire->getTrace()) {
			nameString = tr("Trace wire %1").arg(autoroutable);
		}
	}
	else {
		 nameString = modelPart->description();
	}
	partTitle(nameString, modelPart->version(), modelPart->url(), modelPart->isObsolete());
    m_lockFrame->setVisible(false);
    m_lockLabel->setVisible(false);
    m_locationFrame->setVisible(false);
    m_locationLabel->setVisible(false);
    m_rotationFrame->setVisible(false);
    m_rotationLabel->setVisible(false);

	setUpTitle(wire);
	setUpIcons(wire, swappingEnabled);

	displayProps(modelPart, wire, swappingEnabled);

    bool hasLayer = (wire->viewID() == ViewLayer::PCBView) && wire->getViewGeometry().getPCBTrace();
    m_placementFrame->setVisible(hasLayer);
	m_placementLabel->setVisible(hasLayer);

	addTags(modelPart);
}
