WriteDistanceMatrix(ostream &ofs,OBMol &mol)
  {
    int columns = 7;
    unsigned int max, min = 1;
    unsigned int i,j;
    string type;
    OBAtom *atom, *atom2;
    char buffer[BUFF_SIZE];
    double dst;

    max = columns;
    while (max <= mol.NumAtoms() + columns)
      {
        ofs << "\n";
        if (min > mol.NumAtoms())
          break;
        atom = mol.GetAtom(min);

        snprintf(buffer,BUFF_SIZE,"%15s%4d",
                etab.GetSymbol(atom->GetAtomicNum()),
                min);
        ofs << buffer;

        for (i = min + 1; ((i < max) && (i <= mol.NumAtoms())); i++)
          if (i <= mol.NumAtoms())
            {
              atom = mol.GetAtom(i);
              snprintf(buffer,BUFF_SIZE, "%7s%4d",
                      etab.GetSymbol(atom->GetAtomicNum()),
                      i);
              ofs << buffer;
            }
        ofs << "\n";

        snprintf(buffer, BUFF_SIZE, "%14s","");
        ofs << buffer;
        for (i = min; i < max; i++)
          if (i <= mol.NumAtoms())
            {
              ofs << "-----------";
            }

        ofs << "\n";
        for (i = min; i <= mol.NumAtoms(); i++)
          {
            atom = mol.GetAtom(i);
            snprintf(buffer, BUFF_SIZE, "%4s%4d",
                    etab.GetSymbol(atom->GetAtomicNum()),
                    i);
            ofs << buffer;
            for (j = min; j < max; j++)
              if (j <= i)
                {
                  atom2 = mol.GetAtom(j);
                  dst = SQUARE(atom->GetX() - atom2->GetX());
                  dst += SQUARE(atom->GetY() - atom2->GetY());
                  dst += SQUARE(atom->GetZ() - atom2->GetZ());
                  dst = sqrt(dst);
                  snprintf(buffer, BUFF_SIZE, "%10.4f ",dst);
                  ofs << buffer;
                }
            ofs << "\n";
          }
        max += columns - 1;
        min += columns - 1;
      }
    ofs << "\n";
  }
