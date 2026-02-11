__putchar(int ch) {
	if (serialSTDIO) {
		serialWrite(serialSTDIO, ch);
	}

	return ch;
}
