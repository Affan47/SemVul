APar_FindEndingAtom() {
    short end_atom_num = 0;
    while (true) {
        if ((parsedAtoms[end_atom_num].NextAtomNumber == 0) || (end_atom_num == atom_number - 1)) {
            break;
        }
        else {
            end_atom_num = parsedAtoms[end_atom_num].NextAtomNumber;
        }
    }
    return end_atom_num;
}
