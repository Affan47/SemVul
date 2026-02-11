canDragWire(Wire * wire) {
	if (wire == NULL) return false;

	if (wire->getRatsnest()) return false;

	return true;
}
