Symmetrize(OBMol *mol)
  {
    if (!d->Setup) {

      Setup(mol);
      IdentifyPointGroup();
    }


    if (d->InversionCentersCount) {
      PointGroupPrivate::SYMMETRY_ELEMENT *center = d->InversionCenters[0];
      d->establish_pairs(center);
      d->clean_paired_atoms(center);
    }


    for (unsigned int i = 0; i < d->PlanesCount; i++)
      {
        d->establish_pairs(d->Planes[i]);
        d->clean_paired_atoms(d->Planes[i]);
      }


    for (unsigned int i = 0; i < d->NormalAxesCount; i++)
      {
        d->establish_pairs(d->NormalAxes[i]);
        d->clean_paired_atoms(d->NormalAxes[i]);
      }


    for (unsigned int i = 0; i < d->ImproperAxesCount; i++)
      {
        d->establish_pairs(d->ImproperAxes[i]);
        d->clean_paired_atoms(d->ImproperAxes[i]);
      }


    OBAtom *atom;
    FOR_ATOMS_OF_MOL(a, d->_mol)
      {
        atom = mol->GetAtom(a->GetIdx());
        atom->SetVector(a->GetVector());
      }
  }
