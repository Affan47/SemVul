ParseLine(const char *buffer)
  {
    vector<string> vs;
    vector<int>    bovector;
    OBSmartsPattern *sp;

    if (buffer[0] != '#')
      {
        tokenize(vs,buffer);


        if (vs.size() < 4)
          return;
        else if (vs.size() >= 4 && (vs.size() % 3 != 1))
          {
            stringstream errorMsg;
            errorMsg << " Error in OBBondTyper. Pattern is incorrect, found "
                     << vs.size() << " tokens." << endl;
            errorMsg << " Buffer is: " << buffer << endl;
            obErrorLog.ThrowError(__FUNCTION__, errorMsg.str(), obInfo);
            return;
          }

        sp = new OBSmartsPattern;
        if (sp->Init(vs[0]))
          {
            for (unsigned int i = 1; i < vs.size() ; ++i)
              {
                bovector.push_back( atoi((char *)vs[i].c_str()) );
              }
            _fgbonds.push_back(pair<OBSmartsPattern*,vector<int> >
                               (sp, bovector));
          }
        else
          {
            delete sp;
            sp = NULL;
          }
      }
  }
