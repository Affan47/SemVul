EnsureEndElement(void)
{
  if (_tempAtom.GetAtomicNum() != 0)
  {
    _pmol->AddAtom(_tempAtom);
    atoms[_tempAtom.GetIdx()] = _pmol->NumAtoms();
    _tempAtom.Clear();
  }
  else if (Order >= 0)
  {
    _pmol->AddBond(Begin, End, Order, Flag);
	Order = -1;
  }
}
