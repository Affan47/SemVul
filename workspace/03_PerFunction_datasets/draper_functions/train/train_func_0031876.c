setVoltage(double v, bool doEmit) {
	if (doEmit) {
		emit setVoltageSignal(v, false);
	}
}
