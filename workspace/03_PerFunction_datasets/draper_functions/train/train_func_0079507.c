APar_freefree(int purge_level) {
	modified_atoms = true;
	short eval_atom = 0;
	short prev_atom = 0;
	short moov_atom = 0;
	short mdat_atom = 0;

	if (purge_level == -1) {
		complete_free_space_erasure = true;
	}

	while (true) {
		prev_atom = eval_atom;
		eval_atom = parsedAtoms[eval_atom].NextAtomNumber;
		if (eval_atom == 0) {
			break;
		}

		if ( memcmp(parsedAtoms[eval_atom].AtomicName, "free", 4) == 0 || memcmp(parsedAtoms[eval_atom].AtomicName, "skip", 4) == 0 ) {

			if ( purge_level == -1 || purge_level >= parsedAtoms[eval_atom].AtomicLevel ||
			     (purge_level == 0 && parsedAtoms[eval_atom].AtomicLevel == 1 && (moov_atom == 0 || mdat_atom != 0)) ) {
				short prev_atom = APar_FindPrecedingAtom(eval_atom);
				if (parsedAtoms[eval_atom].NextAtomNumber == 0) {
					APar_EliminateAtom(eval_atom, parsedAtoms[eval_atom].NextAtomNumber);
					parsedAtoms[prev_atom].NextAtomNumber = 0;
				} else {
					APar_EliminateAtom(eval_atom, parsedAtoms[eval_atom].NextAtomNumber);
				}
				eval_atom = prev_atom;
			}
		}
		if ( memcmp(parsedAtoms[eval_atom].AtomicName, "moov", 4) == 0 ) {
			moov_atom = eval_atom;
		}
		if ( memcmp(parsedAtoms[eval_atom].AtomicName, "mdat", 4) == 0 ) {
			mdat_atom = eval_atom;
		}
	}
	return;
}
