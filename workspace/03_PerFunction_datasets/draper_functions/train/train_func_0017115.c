WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;


    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;

    char buffer[BUFF_SIZE];

    snprintf(buffer, BUFF_SIZE, "TITLE %s\n\n", mol.GetTitle());
    ofs << buffer;


    snprintf(buffer, BUFF_SIZE, "CHARGE %d  %d\n\n",
             mol.GetTotalCharge(),
             mol.GetTotalSpinMultiplicity() - 1);
    ofs << buffer;


    snprintf(buffer, BUFF_SIZE, "Number of atoms\n %d\n\n", mol.NumAtoms());
    ofs << buffer;

    ofs << "ATOMS Cartesian\n";
    FOR_ATOMS_OF_MOL(atom, mol)
      {
        snprintf(buffer, BUFF_SIZE, "%-3s%15.5f%15.5f%15.5f\n",
                 etab.GetSymbol(atom->GetAtomicNum()),
                 atom->GetX(),
                 atom->GetY(),
                 atom->GetZ());
        ofs << buffer;
      }
    ofs << "End\n\n";


    const char *keywords = pConv->IsOption("k",OBConversion::OUTOPTIONS);
    const char *keywordFile = pConv->IsOption("f",OBConversion::OUTOPTIONS);


    if (keywordFile) {
        ifstream kfstream(keywordFile);
        string keyBuffer;
        if (kfstream)
          {
            while (getline(kfstream, keyBuffer))
              ofs << keyBuffer << endl;
          }
      }
    else if (keywords) {
      ofs << keywords << endl;
    }
    else {
      ofs << "Basis\n";
      ofs << "End\n\n";

      ofs << "Geometry\n";
      ofs << "End\n\n";
    }

    ofs << endl;

    return true;
  }
