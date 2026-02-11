createTempWireForDragging(Wire * fromWire, ModelPart * wireModel, ConnectorItem * connectorItem, ViewGeometry & viewGeometry, ViewLayer::ViewLayerPlacement spec)
{
	viewGeometry.setSchematicTrace(true);
	Wire * wire =  SketchWidget::createTempWireForDragging(fromWire, wireModel, connectorItem, viewGeometry, spec);
	if (fromWire) {
		wire->setColorString(fromWire->colorString(), fromWire->opacity());
	}
	else {
		wire->setProperty(PCBSketchWidget::FakeTraceProperty, true);
		wire->setColorString(traceColor(connectorItem), 1.0);
	}
	return wire;
}
