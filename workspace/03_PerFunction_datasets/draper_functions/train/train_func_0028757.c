APar_FlagTrackHeader(AtomicInfo* thisAtom) {
	AtomicInfo* trak_atom = NULL;
	AtomicInfo* track_header_atom = NULL;
	short current_atom_idx = thisAtom->AtomicNumber;
	short current_level = thisAtom->AtomicLevel;

	if (thisAtom->AtomicLevel >= 3) {
		while (true) {
			short parent_atom = APar_FindParentAtom(current_atom_idx, current_level);
			current_atom_idx = parent_atom;
			current_level = parsedAtoms[parent_atom].AtomicLevel;

			if (current_level == 2) {
				if (memcmp(parsedAtoms[parent_atom].AtomicName, "trak", 4) == 0) {
					trak_atom = &parsedAtoms[parent_atom];
				}
				break;
			} else if (current_level == 1) {
				break;
			}
		}
		if (trak_atom != NULL) {
			track_header_atom = APar_FindChildAtom(trak_atom->AtomicNumber, "tkhd");
			if (track_header_atom != NULL) {
				track_header_atom->ancillary_data = 0x666C6167;
			}
		}
	}
	APar_FlagMovieHeader();
	return;
}
