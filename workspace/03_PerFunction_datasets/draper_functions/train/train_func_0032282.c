WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;


    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    unsigned int i, file_num = 1;
    string str,str1;
    char buffer[BUFF_SIZE];
    OBAtom *atom;
    OBBond *bond;
    vector<OBBond*>::iterator j;
    char bond_char;


    ofs << "mol " << file_num << " \"" << mol.GetTitle() << "\"\n";

    for(i = 1;i <= mol.NumAtoms(); i++)
      {
        atom = mol.GetAtom(i);
        snprintf(buffer, BUFF_SIZE, "atom %d - %-3s **  - %8.5f %8.5f  %8.5f  %8.5f %d ",
                i,
                etab.GetSymbol(atom->GetAtomicNum()),
                atom->GetPartialCharge(),
                atom->GetX(),
                atom->GetY(),
                atom->GetZ(),
                atom->GetValence());
        ofs << buffer;
        for (bond = atom->BeginBond(j); bond; bond = atom->NextBond(j))
          {
            switch(bond->GetBO())
              {
              case 1 :
                bond_char = 's';
                break;
              case 2 :
                bond_char = 'd';
                break;
              case 3 :
                bond_char = 't';
                break;
              case 5 :
                bond_char = 'a';
                break;
              default:
                bond_char = 's';
                break;
              }
            if (bond->IsAromatic())
              bond_char = 'a';

            snprintf(buffer,BUFF_SIZE, "%d %c ", (bond->GetNbrAtom(atom))->GetIdx(), bond_char);
            ofs << buffer;
          }
        ofs << endl;
      }
    ofs << "endmol " << file_num << endl;
    return(true);
  }
