IsSuppressedHydrogen(OBAtom *atom)
  {
    if (atom->GetIsotope() != 0)
      return false;
    if (atom->GetValence() != 1)
      return false;

    FOR_NBORS_OF_ATOM(nbr, atom) {
      if (nbr->GetAtomicNum() == 1)
        return false;
    }

    return true;
  }
