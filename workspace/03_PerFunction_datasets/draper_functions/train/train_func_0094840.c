WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;


    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    char buffer[BUFF_SIZE];

    ofs << mol.GetTitle() << endl;
    ofs << " " << mol.NumAtoms() << " " << mol.NumBonds() << endl;

    OBAtom *atom;
    vector<OBAtom*>::iterator i;

    for(atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        snprintf(buffer, BUFF_SIZE, " %9.4f %9.4f    0.0000 %-1s",
                 atom->x(),
                 atom->y(),
                 etab.GetSymbol(atom->GetAtomicNum()));
        ofs << buffer << endl;
      }

    OBBond *bond;
    vector<OBBond*>::iterator j;

    for(bond = mol.BeginBond(j);bond;bond = mol.NextBond(j))
      {
        snprintf(buffer, BUFF_SIZE, "%3d%3d%3d%3d",
                 bond->GetBeginAtomIdx(),
                 bond->GetEndAtomIdx(),
                 bond->GetBO(), bond->GetBO());
        ofs << buffer << endl;
      }
    return(true);
  }
