SetTypes()
  {
    vector<vector<int> > _mlist;
    vector<pair<OBSmartsPattern*,string> > _vexttyp;
    vector<vector<int> >::iterator j;
    vector<pair<OBSmartsPattern*,string> >::iterator i;
    OBSmartsPattern *sp;
    vector<string> vs;
    char buffer[80];

    _mol.SetAtomTypesPerceived();


    ifstream ifs;
    if (OpenDatafile(ifs, "ghemical.prm").length() == 0) {
      obErrorLog.ThrowError(__FUNCTION__, "Cannot open ghemical.prm", obError);
      return false;
    }


    obLocale.SetLocale();

    while (ifs.getline(buffer, 80)) {
      if (EQn(buffer, "atom", 4)) {
      	tokenize(vs, buffer);

        sp = new OBSmartsPattern;
        if (sp->Init(vs[1]))
          _vexttyp.push_back(pair<OBSmartsPattern*,string> (sp,vs[2]));
        else {
          delete sp;
          sp = NULL;
          obErrorLog.ThrowError(__FUNCTION__, " Could not parse atom type table from ghemical.prm", obInfo);
          return false;
        }
      }
    }

    for (i = _vexttyp.begin();i != _vexttyp.end();++i) {
      if (i->first->Match(_mol)) {
        _mlist = i->first->GetMapList();
        for (j = _mlist.begin();j != _mlist.end();++j) {
          _mol.GetAtom((*j)[0])->SetType(i->second);
        }
      }
    }

    SetPartialCharges();

    IF_OBFF_LOGLVL_LOW {
      OBFFLog("\nA T O M   T Y P E S\n\n");
      OBFFLog("IDX\tTYPE\n");

      FOR_ATOMS_OF_MOL (a, _mol) {
        snprintf(_logbuf, BUFF_SIZE, "%d\t%s\n", a->GetIdx(), a->GetType());
        OBFFLog(_logbuf);
      }

      OBFFLog("\nC H A R G E S\n\n");
      OBFFLog("IDX\tCHARGE\n");

      FOR_ATOMS_OF_MOL (a, _mol) {
        snprintf(_logbuf, BUFF_SIZE, "%d\t%f\n", a->GetIdx(), a->GetPartialCharge());
        OBFFLog(_logbuf);
      }
    }


    if (ifs)
      ifs.close();


    obLocale.RestoreLocale();

    return true;
  }
