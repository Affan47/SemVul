ReadMolecule(OBBase* pOb, OBConversion* pConv)
  {

    OBMol* pmol = pOb->CastAndClear<OBMol>();
    if(pmol==NULL)
      return false;


    istream &ifs = *pConv->GetInStream();
    OBMol &mol = *pmol;
    mol.SetTitle( pConv->GetTitle());

    char buffer[BUFF_SIZE];

    if (!ifs.getline(buffer,BUFF_SIZE))
      {
        obErrorLog.ThrowError(__FUNCTION__, "File is empty!", obError);
        return(false);
      }
    if (!strstr(buffer,"<Property"))
      {
        obErrorLog.ThrowError(__FUNCTION__, "Not valid CRK XML", obWarning);
        return false;
      }
    if (!strstr(buffer,"\"ModelStructure\"") && !strstr(buffer,"\"XRayStructure\""))
      {
        obErrorLog.ThrowError(__FUNCTION__,"Not CRK ModelStructure or XRayStructure (3D).", obWarning);
        return false;
      }

    return CRK2DFormat::ReadCRK(ifs,mol,"Structure3D");
  }
