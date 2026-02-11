WriteChiral(ostream &ofs,OBMol &mol)
  {
    OBAtom *atom;
    vector<OBAtom*>::iterator i;
    char buffer[BUFF_SIZE];

    for (atom = mol.BeginAtom(i);atom;atom = mol.NextAtom(i))
      {
        if (atom->IsChiral())
          {


            ofs << buffer << "\n";
          }
      }
  }
