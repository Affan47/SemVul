Clone(OBBase* newparent) const
  {


    OBMol* newmol = static_cast<OBMol*>(newparent);

    OBRotamerList *new_rml = new OBRotamerList;
    new_rml->_attr = _attr;
    new_rml->_type = _type;


    unsigned int k,l;
    vector<double*> bc;
    double *c=NULL;
    double *cc=NULL;
    for (k=0 ; k<NumBaseCoordinateSets() ; ++k)
      {
        c = new double [3*NumAtoms()];
        cc = GetBaseCoordinateSet(k);
        for (l=0 ; l<3*NumAtoms() ; ++l)
					c[l] = cc[l];
        bc.push_back(c);
      }
    if (NumBaseCoordinateSets())
			new_rml->SetBaseCoordinateSets(bc,NumAtoms());


    unsigned char *ref = new unsigned char [NumRotors()*4];
    if (ref)
      {
        GetReferenceArray(ref);
        new_rml->Setup(*newmol,ref,NumRotors());
        delete [] ref;
      }


    unsigned char *rotamers = new unsigned char [(NumRotors()+1)*NumRotamers()];
    if (rotamers)
      {
        vector<unsigned char*>::const_iterator kk;
        unsigned int idx=0;
        for (kk = _vrotamer.begin();kk != _vrotamer.end();++kk)
          {
            memcpy(&rotamers[idx],(const unsigned char*)*kk,sizeof(unsigned char)*(NumRotors()+1));
            idx += sizeof(unsigned char)*(NumRotors()+1);
          }
        new_rml->AddRotamers(rotamers,NumRotamers());
        delete [] rotamers;
      }
    return new_rml;
  }
