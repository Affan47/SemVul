M91IRQHook(void) {
	if (IRQCount < 8 && IRQa) {
		IRQCount++;
		if (IRQCount >= 8) {
			X6502_IRQBegin(FCEU_IQEXT);
		}
	}
}
