APar_FindLastAtom() {
    short this_atom_num = 0;
    while (parsedAtoms[this_atom_num].NextAtomNumber != 0) {
        this_atom_num = parsedAtoms[this_atom_num].NextAtomNumber;
    }
    return this_atom_num;
}
