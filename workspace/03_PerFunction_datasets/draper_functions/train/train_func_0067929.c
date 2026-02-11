InsertLine(int line) {
	if (lineStates.Length()) {
		lineStates.EnsureLength(line);
		int val = (line < lineStates.Length()) ? lineStates[line] : 0;
		lineStates.Insert(line, val);
	}
}
