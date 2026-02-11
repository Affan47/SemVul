DeleteAtom(OBAtom *atom, bool destroyAtom)
  {
    if (atom->IsHydrogen())
      return(DeleteHydrogen(atom));

    BeginModify();


    OBAtom *nbr;
    vector<OBBond*> vdb;
    vector<OBBond*>::iterator j;
    for (nbr = atom->BeginNbrAtom(j);nbr;nbr = atom->NextNbrAtom(j))
      vdb.push_back(*j);

    for (j = vdb.begin();j != vdb.end();++j)
      DeleteBond((OBBond *)*j);

    _atomIds[atom->GetId()] = (OBAtom*)NULL;
    _vatom.erase(_vatom.begin()+(atom->GetIdx()-1));
    _natoms--;


    int idx;
    vector<OBAtom*>::iterator i;
    OBAtom *atomi;
    for (idx=1,atomi = BeginAtom(i);atomi;atomi = NextAtom(i),++idx)
      atomi->SetIdx(idx);

    EndModify();


    OBStereo::Ref id = atom->GetId();
    DeleteStereoOnAtom(*this, id);

    if (destroyAtom)
      DestroyAtom(atom);

    UnsetSSSRPerceived();
    UnsetLSSRPerceived();
    return(true);
  }
