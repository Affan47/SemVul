ReadMolecule(OBBase* pOb, OBConversion* pConv)
  {

    bool ok;


    levcfg=0;
    imcon=0;
    forces.clear();

    OBMol* pmol = pOb->CastAndClear<OBMol>();
    if(pmol==NULL)
      return false;


    std::istream &ifs = *pConv->GetInStream();
    OBMol &mol = *pmol;

    if ( ! ParseHeader( ifs, mol ) ) return false;


    if ( imcon > 0 ) ParseUnitCell( ifs, mol );

    mol.BeginModify();
    ok = true;
    while ( ok )
      {
        ok = ReadAtom( ifs, mol );
      }


    if ( levcfg > 1 && forces.size() )
      {
        OBConformerData * conformer = new OBConformerData();
        std::vector< std::vector< vector3 > > conflist;
        conflist.push_back( forces );
        conformer->SetForces( conflist );
        mol.SetData( conformer );
      }

    mol.EndModify();

    if ( mol.NumAtoms() == 0 )
      return(false);
    else
      return(true);

  }
