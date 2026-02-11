wireSplitSlot(Wire* wire, QPointF newPos, QPointF oldPos, QLineF oldLine) {
	if (!wire->getRatsnest()) {
		SketchWidget::wireSplitSlot(wire, newPos, oldPos, oldLine);
	}

	createTrace(wire, false);
}
