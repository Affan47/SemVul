ContigFragList(std::vector<std::vector<int> >&cfl)
  {
    int j;
    OBAtom *atom;
    OBBond *bond;
    vector<OBAtom*>::iterator i;
    vector<OBBond*>::iterator k;
    OBBitVec used,curr,next,frag;
    vector<int> tmp;

    used.Resize(NumAtoms()+1);
    curr.Resize(NumAtoms()+1);
    next.Resize(NumAtoms()+1);
    frag.Resize(NumAtoms()+1);

    while ((unsigned)used.CountBits() < NumAtoms())
      {
        curr.Clear();
        frag.Clear();
        for (atom = BeginAtom(i);atom;atom = NextAtom(i))
          if (!used.BitIsOn(atom->GetIdx()))
            {
              curr.SetBitOn(atom->GetIdx());
              break;
            }

        frag |= curr;
        while (!curr.IsEmpty())
          {
            next.Clear();
            for (j = curr.NextBit(-1);j != curr.EndBit();j = curr.NextBit(j))
              {
                atom = GetAtom(j);
                for (bond = atom->BeginBond(k);bond;bond = atom->NextBond(k))
                  if (!used.BitIsOn(bond->GetNbrAtomIdx(atom)))
                    next.SetBitOn(bond->GetNbrAtomIdx(atom));
              }

            used |= curr;
            used |= next;
            frag |= next;
            curr = next;
          }

        tmp.clear();
        frag.ToVecInt(tmp);
        cfl.push_back(tmp);
      }

    sort(cfl.begin(),cfl.end(),SortVVInt);
  }
