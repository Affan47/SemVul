APar_ReturnChildrenAtoms(short this_atom, uint8_t atom_index) {
    short child_atom = 0;
    uint8_t total_children = 0;
    short iter = parsedAtoms[this_atom].NextAtomNumber;

    while (true) {
        if ((parsedAtoms[iter].AtomicLevel == parsedAtoms[this_atom].AtomicLevel + 1 && this_atom > 0)
                || (this_atom == 0 && parsedAtoms[iter].AtomicLevel == 1)) {
            total_children++;

            if (atom_index == total_children) {
                child_atom = iter;
                break;
            }
        }
        if (parsedAtoms[iter].AtomicLevel <= parsedAtoms[this_atom].AtomicLevel && this_atom != 0) {
            break;
        }
        else {
            iter = parsedAtoms[iter].NextAtomNumber;
        }
        if (iter == 0) {
            break;
        }
    }
    if (atom_index == 0) {
        child_atom = (short) total_children;
    }
    return child_atom;
}
