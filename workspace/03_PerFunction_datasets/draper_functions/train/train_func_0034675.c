ReadAtomBlock(istream& ifs,OBMol& mol, OBConversion* pConv)
  {
    OBAtom atom;
    bool chiralWatch=false;
    int obindex;
    for(obindex=1;;obindex++)
      {
        if(!ReadV3000Line(ifs,vs)) return false;
        if(vs[2]=="END") break;

        indexmap[ReadUIntField(vs[2].c_str())] = obindex;
        atom.SetVector(atof(vs[4].c_str()), atof(vs[5].c_str()), atof(vs[6].c_str()));


        char type[5];
        strncpy(type,vs[3].c_str(),5);
        type[4] = '\0';
        if(!strcmp(type, "R#"))
          {
          obErrorLog.ThrowError(__FUNCTION__,
            "A molecule contains an R group which are not currently implemented"
            , obWarning, onceOnly);
          atom.SetAtomicNum(0);
          }
        else
          {
          int iso=0;
          atom.SetAtomicNum(etab.GetAtomicNum(type,iso));
          if(iso)
            atom.SetIsotope(iso);
          atom.SetType(type);


          vector<string>::iterator itr;
          for(itr=vs.begin()+8;itr!=vs.end();itr++)
            {
              string::size_type pos = (*itr).find('=');
              if (pos==string::npos) return false;
              int val = ReadIntField((*itr).substr(pos+1).c_str());

              if((*itr).substr(0,pos)=="CHG")
                {
                  atom.SetFormalCharge(val);
                }
              else if((*itr).substr(0,pos)=="RAD")
                {
                  atom.SetSpinMultiplicity(val);
                }
              else if((*itr).substr(0,pos)=="CFG")
                {


                }
              else if((*itr).substr(0,pos)=="MASS")
                {
                  if(val) atom.SetIsotope(val);
                }
              else if((*itr).substr(0,pos)=="VAL")
                {

                }


            }
          }
        if(!mol.AddAtom(atom)) return false;


        atom.Clear();
      }
    return true;
  }
