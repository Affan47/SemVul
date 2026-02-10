ReadMolecule(OBBase* pOb, OBConversion* pConv)
  {
    OBMol* pmol = pOb->CastAndClear<OBMol>();
    if (!pmol)
      return false;


    istream& ifs = *pConv->GetInStream();


    std::string smiles;
    std::getline(ifs, smiles);


    std::size_t space_pos = smiles.find(" ");
    std::size_t tab_pos = smiles.find("\t");
    if (space_pos != std::string::npos && tab_pos != std::string::npos)
      space_pos = std::min(space_pos, tab_pos);
    else if (tab_pos != std::string::npos)
      space_pos = tab_pos;

    if (space_pos != std::string::npos) {
      while (space_pos < smiles.size() && (smiles[space_pos] == ' ' || smiles[space_pos] == '\t'))
        ++space_pos;
      pmol->SetTitle(smiles.substr(space_pos).c_str());
    }

    pmol->BeginModify();
    pmol->SetDimension(0);


    OpenBabelCallback callback(pmol);
    Smiley::Parser<OpenBabelCallback> parser(callback);

    try {
      parser.parse(smiles);
    } catch (Smiley::Exception &e) {
      if (e.type() == Smiley::Exception::SyntaxError)
        std::cerr << "Syntax";
      else
        std::cerr << "Semantics";
      std::cerr << "Error: " << e.what() << "." << std::endl;
      std::cerr << smiles << std::endl;
      for (std::size_t i = 0; i < e.pos(); ++i)
        std::cerr << " ";
      for (std::size_t i = 0; i < e.length(); ++i)
        std::cerr << "^";
      std::cerr << std::endl;
    }

    pmol->EndModify();


    pmol->SetAromaticPerceived();

    OBAtomTyper typer;
    typer.AssignImplicitValence(*pmol);


    FOR_ATOMS_OF_MOL (atom, pmol) {
      if (atom->IsNitrogen() && atom->IsAromatic() &&  atom->GetValence() == 2)
        atom->SetImplicitValence(2);
    }


    CreateCisTrans(pmol, callback.upDown);
    StereoFrom0D(pmol);

    return true;
  }
