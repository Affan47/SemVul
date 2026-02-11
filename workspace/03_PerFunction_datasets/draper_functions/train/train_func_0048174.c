APar_SampleTableIterator(FILE *file) {
	uint8_t total_tracks = 0;
	uint8_t a_track = 0;
	char track_path[36];
	memset(track_path, 0, 36);
	AtomicInfo* samples_parent = NULL;
	AtomicInfo* chunk_offset_atom = NULL;

	APar_FindAtomInTrack(total_tracks, a_track, NULL);
	for (uint8_t trk_idx=1; trk_idx <= total_tracks; trk_idx++) {
		sprintf(track_path, "moov.trak[%hhu].mdia.minf.stbl", trk_idx);
		samples_parent = APar_FindAtom(track_path, false, SIMPLE_ATOM, 0, false);
		if (samples_parent != NULL) {
			chunk_offset_atom = APar_FindChildAtom(samples_parent->AtomicNumber, "stco");
			if (chunk_offset_atom == NULL) chunk_offset_atom = APar_FindChildAtom(samples_parent->AtomicNumber, "co64");
			if (chunk_offset_atom != NULL) {
				APar_LocateDataReference(chunk_offset_atom->AtomicNumber, file);
			}
		}
	}
	return;
}
