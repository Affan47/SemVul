NeedShown(int pos, int len) {
	if (foldAutomatic & SC_AUTOMATICFOLD_SHOW) {
		int lineStart = pdoc->LineFromPosition(pos);
		int lineEnd = pdoc->LineFromPosition(pos+len);
		for (int line = lineStart; line <= lineEnd; line++) {
			EnsureLineVisible(line, false);
		}
	} else {
		NotifyNeedShown(pos, len);
	}
}
