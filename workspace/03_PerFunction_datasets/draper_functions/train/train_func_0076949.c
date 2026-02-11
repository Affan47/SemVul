APar_DetermineAtomLengths() {

    if (!udta_dynamics.dynamic_updating && !psp_brand && initial_optimize_pass) {
        APar_Optimize(false);
    }
    else {

        udta_dynamics.moov_atom = APar_FindAtom("moov", false, SIMPLE_ATOM, 0)->AtomicNumber;
        AtomicInfo* udta_atom = APar_FindAtom("moov.udta", false, SIMPLE_ATOM, 0);
        if (udta_atom != NULL) {
            udta_dynamics.last_udta_child_atom = APar_FindLastChild_of_ParentAtom(udta_atom->AtomicNumber);
        }
    }

    short rev_atom_loop = APar_FindLastAtom();


    while (true) {
        short next_atom = 0;
        uint32_t atom_size = 0;

        if (rev_atom_loop == 0) {
            break;
        }

        uint32_t _atom_ = UInt32FromBigEndian(parsedAtoms[rev_atom_loop].AtomicName);
        switch (_atom_) {
        case 0x6D657461:
            atom_size += 12;
            break;

        case 0x73747364:
            atom_size += 16;
            break;

        default:
            atom_size += 8;
            break;
        }

        if (parsedAtoms[rev_atom_loop].NextAtomNumber != 0) {
            next_atom = parsedAtoms[rev_atom_loop].NextAtomNumber;
        }

        while (parsedAtoms[next_atom].AtomicLevel > parsedAtoms[rev_atom_loop].AtomicLevel) {
            if (parsedAtoms[rev_atom_loop].AtomicLevel == (parsedAtoms[next_atom].AtomicLevel - 1)) {
                atom_size += parsedAtoms[next_atom].AtomicLength;
            }
            else if (parsedAtoms[next_atom].AtomicLevel < parsedAtoms[rev_atom_loop].AtomicLevel) {
                break;
            }
            next_atom = parsedAtoms[next_atom].NextAtomNumber;
            parsedAtoms[rev_atom_loop].AtomicLength = atom_size;
        }

        if (_atom_ == 0x75647461
                && parsedAtoms[rev_atom_loop].AtomicLevel
                        > parsedAtoms[parsedAtoms[rev_atom_loop].NextAtomNumber].AtomicLevel) {
            parsedAtoms[rev_atom_loop].AtomicLength = 8;
        }
        if (_atom_ == 0x6D657461
                && parsedAtoms[rev_atom_loop].AtomicLevel
                        != parsedAtoms[parsedAtoms[rev_atom_loop].NextAtomNumber].AtomicLevel - 1) {
            parsedAtoms[rev_atom_loop].AtomicLength = 12;
        }
        if (_atom_ == 0x696C7374
                && parsedAtoms[rev_atom_loop].AtomicLevel
                        != parsedAtoms[parsedAtoms[rev_atom_loop].NextAtomNumber].AtomicLevel - 1) {
            parsedAtoms[rev_atom_loop].AtomicLength = 8;
        }

        rev_atom_loop = APar_FindPrecedingAtom(parsedAtoms[rev_atom_loop].AtomicNumber);

    }
    APar_DetermineNewFileLength();


    return;
}
