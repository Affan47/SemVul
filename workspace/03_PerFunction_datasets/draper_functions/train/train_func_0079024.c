WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;


    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    char tmptype[16];
    char buffer[BUFF_SIZE];

    if (strlen(mol.GetTitle()) > 0)
      ofs << mol.GetTitle() << endl;
    else
      ofs << "Untitled" << endl;

    snprintf(buffer,BUFF_SIZE,"%d",mol.NumAtoms());
    ofs << buffer << endl;

    OBAtom *atom,*nbr;
    vector<OBAtom*>::iterator i;
    vector<OBBond*>::iterator j;

    for(atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        strncpy(tmptype,etab.GetSymbol(atom->GetAtomicNum()), sizeof(tmptype));
        tmptype[15] = '\0';
        if (strlen(tmptype) > 1)
          tmptype[1] = toupper(tmptype[1]);
        snprintf(buffer,BUFF_SIZE,"%-3s %8.4f  %8.4f  %8.4f",
                 tmptype,
                 atom->GetX(),
                 atom->GetY(),
                 atom->GetZ());
        ofs << buffer;
        for (nbr = atom->BeginNbrAtom(j);nbr;nbr = atom->NextNbrAtom(j))
          {
            snprintf(buffer, BUFF_SIZE, "%6d",nbr->GetIdx());
            ofs << buffer;
          }
        ofs << endl;
      }

    return(true);
  }
