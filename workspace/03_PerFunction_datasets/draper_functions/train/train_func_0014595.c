DeleteMark(int line, int markerNum, bool all) {
	bool someChanges = false;
	if (markers.Length() && (line >= 0) && (line < markers.Length()) && markers[line]) {
		if (markerNum == -1) {
			someChanges = true;
			delete markers[line];
			markers[line] = NULL;
		} else {
			bool performedDeletion = markers[line]->RemoveNumber(markerNum);
			someChanges = someChanges || performedDeletion;
			while (all && performedDeletion) {
				performedDeletion = markers[line]->RemoveNumber(markerNum);
				someChanges = someChanges || performedDeletion;
			}
			if (markers[line]->Length() == 0) {
				delete markers[line];
				markers[line] = NULL;
			}
		}
	}
	return someChanges;
}
