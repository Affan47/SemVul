SpaceCount(char* lineBuffer) {
	if (lineBuffer == NULL)
		return 0;

	char* headBuffer = lineBuffer;

	while (*headBuffer == ' ')
		headBuffer++;

	return headBuffer - lineBuffer;
}
