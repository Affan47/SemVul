_serialStartTxDMA(serialPort_t *s, void *buf, int size, serialTxDMACallback_t *txDMACallback, void *txDMACallbackParam) {
	if (!s->txDmaRunning) {
		s->txDmaRunning = 1;

		s->txDMACallback = txDMACallback;
		s->txDMACallbackParam = txDMACallbackParam;

		s->txDMAStream->M0AR = (uint32_t)buf;
		s->txDMAStream->NDTR = size;

		DMA_Cmd(s->txDMAStream, ENABLE);

		return 1;
	} else {
		return 0;
	}
}
