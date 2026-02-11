OutputUnions(ostream &ofs, OBMol &mol, string prefix)
  {

    ofs << endl << "//All atoms of molecule " << prefix << endl;
    ofs << "#ifdef (TRANS)" << endl;
    ofs << "#declare " << prefix << "_atoms = merge {" << endl;
    ofs << "#else" << endl;
    ofs << "#declare " << prefix << "_atoms = union {" << endl;
    ofs << "#end //(End of TRANS)" << endl;


    for(unsigned int i = 1; i <= mol.NumAtoms(); ++i)
      {


        ofs << "\t  object{" << prefix << "_atom" << i << "}" << endl;

      }
    ofs << "\t }" << endl << endl;


    if(mol.NumBonds() > 0)
      {


        ofs << "//Bonds only needed for ball and sticks or capped sticks models" << endl;
        ofs << "#if (BAS | CST)" << endl;
        ofs << "#declare " << prefix <<"_bonds = union {" << endl;


        for(unsigned int i = 0; i < mol.NumBonds(); ++i)
          {


            ofs << "\t  object{" << prefix << "_bond" << i << "}" << endl;

          }


        ofs << "\t }" << endl << "#end" << endl << endl;

      }

  }
