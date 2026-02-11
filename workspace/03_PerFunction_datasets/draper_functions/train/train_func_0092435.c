initWire(Wire * wire, int penWidth) {
	Q_UNUSED(penWidth);
	if (wire->getRatsnest()) return;

	wire->setColorString(traceColor(wire->connector0()), 1.0);
	wire->setPenWidth(1, this, 2);
}
