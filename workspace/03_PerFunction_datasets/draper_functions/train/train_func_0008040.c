DeterminePeptideSidechains(OBMol &mol)
  {
    int resid;
    int max = mol.NumAtoms();

    for (int i = 0 ; i < max ; ++i)
      if (atomids[i] == AI_CA)
        {
          resid = IdentifyResidue(PDecisionTree, mol, i, resnos[i]);
          AssignResidue(mol,resnos[i],chains[i],resid);
        }

    return true;
  }
