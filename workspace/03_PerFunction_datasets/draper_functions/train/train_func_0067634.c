LH53IRQ(int a) {
	if (IRQa) {
		IRQCount += a;
		if (IRQCount > 7560)
			X6502_IRQBegin(FCEU_IQEXT);
	}
}
