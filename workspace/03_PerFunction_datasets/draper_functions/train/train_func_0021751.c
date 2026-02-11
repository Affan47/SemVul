GetFragment(OBAtom *atom)
  {
    OBBitVec fragment;

    fragment.SetBitOn(atom->GetIdx());
    AddNbrs(fragment, atom);

    return fragment;
  }
