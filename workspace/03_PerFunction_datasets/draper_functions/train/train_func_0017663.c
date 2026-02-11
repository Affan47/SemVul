HasLabel(OBAtom *atom)
  {
    if (!atom->IsCarbon())
      return true;
    if ((options & OBDepict::drawAllC) || ((options & OBDepict::drawTermC) && (atom->GetValence() == 1)))
      return true;
    return false;
  }
