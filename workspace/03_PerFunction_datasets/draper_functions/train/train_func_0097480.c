WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;


    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;


    char buffer[BUFF_SIZE];

    ofs << "% " << mol.GetTitle() << "\n";
    ofs << "\n";
    ofs << "molecule:\n";

    FOR_ATOMS_OF_MOL(atom, mol)
      {
        snprintf(buffer, BUFF_SIZE, "%4s  %8.5f  %8.5f  %8.5f \n",
                etab.GetSymbol(atom->GetAtomicNum()),
                atom->GetX(),
                atom->GetY(),
                atom->GetZ());
        ofs << buffer;
      }

    ofs << "\n\n\n";
    return(true);
  }
