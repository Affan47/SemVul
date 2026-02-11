WriteMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = dynamic_cast<OBMol*>(pOb);
    if(pmol==NULL)
      return false;


    model_type = "BAS";
    const char* tmp = pConv->IsOption("m");
    if (tmp) {
      model_type = string(tmp);

      std::transform(model_type.begin(), model_type.end(), model_type.begin(), static_cast< int(*)(int) >(std::toupper));
      if (model_type != "BAS" && model_type != "SPF" && model_type != "CST") {
        obErrorLog.ThrowError(__FUNCTION__, "Unknown model type specified. Using the default instead (\"BAS\", ball-and-stick).\n",obWarning);
        model_type = "BAS";
      }
    }


    trans_texture = pConv->IsOption("t") ? true : false;
    sky = pConv->IsOption("s") ? true : false;
    checkerboard = pConv->IsOption("c") ? true : false;
    sphere = pConv->IsOption("f") ? true : false;


    ostream &ofs = *pConv->GetOutStream();
    OBMol &mol = *pmol;
    const char* title = pmol->GetTitle();

    static long num = 0;
    double min_x, max_x, min_y, max_y, min_z, max_z;


    stringstream ss;
    ss << "mol_" << num;
    string prefix = ss.str();


    if (num == 0)
      {


        OutputHeader(ofs, mol, prefix);

      }
    else
      {


        ostringstream numStr;
        numStr << num << ends;
        prefix += numStr.str().c_str();
      }


    OutputAtoms(ofs, mol, prefix);


    if (mol.NumBonds() > 0)
      {


        ofs << "//Povray-description of bonds 1 - " << mol.NumBonds() << endl;


        ofs << "#if (BAS)" << endl;


        OutputBASBonds(ofs, mol, prefix);


        ofs << "#end //(BAS-Bonds)" << endl << endl;


        ofs << "#if (CST)" << endl;


        OutputCSTBonds(ofs, mol, prefix);


        ofs << "#end // (CST-Bonds)" << endl << endl;

      }


    OutputUnions(ofs, mol, prefix);


    CalcBoundingBox(mol, min_x, max_x, min_y, max_y, min_z, max_z);


    if (mol.NumBonds() > 0)
      {


        OutputMoleculeBonds(ofs,
                            prefix,
                            min_x, max_x,
                            min_y, max_y,
                            min_z, max_z);

      }
    else
      {


        OutputMoleculeNoBonds(ofs, prefix);

      }


    OutputCenterComment(ofs,
                        prefix,
                        min_x, max_x,
                        min_y, max_y,
                        min_z, max_z);


    ofs << prefix << endl;


    num++;


    return(true);
  }
