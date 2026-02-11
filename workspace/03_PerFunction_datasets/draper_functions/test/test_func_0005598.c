SetCoordinates(OBMol &mol)
  {
    OBAtom *atom;

    if (_mol.NumAtoms() != mol.NumAtoms())
      return false;


    FOR_ATOMS_OF_MOL (a, mol) {
      atom = _mol.GetAtom(a->GetIdx());
      atom->SetVector(a->GetVector());
    }

    return true;
  }
