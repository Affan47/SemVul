sigHandlerIO(int signumber) {
	if (queuebuffer) {
		char buffer[64];
		int bytes;
		while ((bytes = read(uartfd, buffer, 64)) > 0)
			qb_push(queuebuffer, buffer, bytes);
	}
}
