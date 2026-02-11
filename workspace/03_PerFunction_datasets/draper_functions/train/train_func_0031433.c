createTrace(Wire * wire, bool useLastWireColor) {
	QString commandString = tr("Create Trace from Ratsnest");
	SketchWidget::createTrace(wire, commandString, getTraceFlag(), useLastWireColor);
	ensureTraceLayerVisible();
}
