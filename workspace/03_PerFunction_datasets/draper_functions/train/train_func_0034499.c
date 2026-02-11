ParseLine(const char *buffer)
  {
    vector<string> vs;
    OBSmartsPattern *sp;

    if (EQn(buffer,"RINGTYP",7)) {
      tokenize(vs,buffer);
      if (vs.size() < 3) {
        obErrorLog.ThrowError(__FUNCTION__, " Could not parse RING line in ring type table from ringtyp.txt", obInfo);
        return;
      }
      sp = new OBSmartsPattern;
      if (sp->Init(vs[2]))
        _ringtyp.push_back(pair<OBSmartsPattern*,string> (sp,vs[1]));
      else {
        delete sp;
        sp = NULL;
        obErrorLog.ThrowError(__FUNCTION__, " Could not parse RING line in ring type table from ringtyp.txt", obInfo);
        return;
      }
    }
  }
