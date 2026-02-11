ClockMMC3Counter(void) {
	int count = IRQCount;
	if (!count || IRQReload) {
		IRQCount = IRQLatch;
		IRQReload = 0;
	} else
		IRQCount--;
	if ((count | isRevB) && !IRQCount) {
		if (IRQa) {
			X6502_IRQBegin(FCEU_IQEXT);
		}
	}
}
