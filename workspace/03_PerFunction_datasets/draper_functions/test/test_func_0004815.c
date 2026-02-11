InitialPartialCharges(OBMol &mol)
  {
    OBAtom *atom;
    vector<OBAtom*>::iterator i;

    for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        if (atom->IsCarboxylOxygen())
          atom->SetPartialCharge(-0.500);
        else if (atom->IsPhosphateOxygen() &&
                 atom->GetHvyValence() == 1)
          atom->SetPartialCharge(-0.666);
        else if (atom->IsSulfateOxygen())
          atom->SetPartialCharge(-0.500);
        else
          atom->SetPartialCharge((double)atom->GetFormalCharge());
      }
  }
