APar_EliminateAtom(short this_atom_number, int resume_atom_number) {
    if (this_atom_number > 0 && this_atom_number < atom_number && resume_atom_number >= 0
            && resume_atom_number < atom_number) {
        short preceding_atom_pos = APar_FindPrecedingAtom(this_atom_number);
        if (APar_Eval_ChunkOffsetImpact(this_atom_number)) {
            removed_bytes_tally += parsedAtoms[this_atom_number].AtomicLength;
        }
        parsedAtoms[preceding_atom_pos].NextAtomNumber = resume_atom_number;

        memset(parsedAtoms[this_atom_number].AtomicName, 0, 4);
        parsedAtoms[this_atom_number].AtomicNumber = -1;
        parsedAtoms[this_atom_number].NextAtomNumber = -1;
    }
    return;
}
