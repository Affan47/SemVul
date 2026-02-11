MoveForInsertDelete(bool insertion, int startChange, int length) {
	if (insertion) {
		if (position == startChange) {
			int virtualLengthRemove = std::min(length, virtualSpace);
			virtualSpace -= virtualLengthRemove;
			position += virtualLengthRemove;
		} else if (position > startChange) {
			position += length;
		}
	} else {
		if (position == startChange) {
			virtualSpace = 0;
		}
		if (position > startChange) {
			int endDeletion = startChange + length;
			if (position > endDeletion) {
				position -= length;
			} else {
				position = startChange;
				virtualSpace = 0;
			}
		}
	}
}
