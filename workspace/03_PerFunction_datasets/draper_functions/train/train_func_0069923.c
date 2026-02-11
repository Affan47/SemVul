DeleteChars(int pos, int len) {
	if (len == 0)
		return false;
	if ((pos + len) > Length())
		return false;
	CheckReadOnly();
	if (enteredModification != 0) {
		return false;
	} else {
		enteredModification++;
		if (!cb.IsReadOnly()) {
			NotifyModified(
			    DocModification(
			        SC_MOD_BEFOREDELETE | SC_PERFORMED_USER,
			        pos, len,
			        0, 0));
			int prevLinesTotal = LinesTotal();
			bool startSavePoint = cb.IsSavePoint();
			bool startSequence = false;
			const char *text = cb.DeleteChars(pos, len, startSequence);
			if (startSavePoint && cb.IsCollectingUndo())
				NotifySavePoint(!startSavePoint);
			if ((pos < Length()) || (pos == 0))
				ModifiedAt(pos);
			else
				ModifiedAt(pos-1);
			NotifyModified(
			    DocModification(
			        SC_MOD_DELETETEXT | SC_PERFORMED_USER | (startSequence?SC_STARTACTION:0),
			        pos, len,
			        LinesTotal() - prevLinesTotal, text));
		}
		enteredModification--;
	}
	return !cb.IsReadOnly();
}
