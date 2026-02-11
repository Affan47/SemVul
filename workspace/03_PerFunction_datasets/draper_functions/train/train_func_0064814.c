SetLineState(int line, int state) {
	int statePrevious = static_cast<LineState *>(perLineData[ldState])->SetLineState(line, state);
	if (state != statePrevious) {
		DocModification mh(SC_MOD_CHANGELINESTATE, LineStart(line), 0, 0, 0, line);
		NotifyModified(mh);
	}
	return statePrevious;
}
