serialStartTxDMA(void *param) {
	serialPort_t *s = (serialPort_t *)param;
	uint32_t tail = s->txTail;
	int size;

	if (!s->txDmaRunning && s->txHead != tail) {
		if (s->txHead > tail) {
			size = s->txHead - tail;
			s->txTail = s->txHead;
		} else {
			size = s->txBufSize - tail;
			s->txTail = 0;
		}

		_serialStartTxDMA(s, (void *)&s->txBuf[tail], size, serialStartTxDMA, s);
	}
}
