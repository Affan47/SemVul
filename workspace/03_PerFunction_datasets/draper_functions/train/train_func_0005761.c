ParseParamVDW(std::string &filename)
  {
    vector<string> vs;
    char buffer[80];

    OBFFParameter parameter;


    ifstream ifs;
    if (OpenDatafile(ifs, filename).length() == 0) {
      obErrorLog.ThrowError(__FUNCTION__, "Cannot open mmffvdw.par", obError);
      return false;
    }

    while (ifs.getline(buffer, 80)) {
      if (EQn(buffer, "*", 1)) continue;
      if (EQn(buffer, "$", 1)) continue;

      tokenize(vs, buffer);

      parameter.clear();
      parameter.a = atoi(vs[0].c_str());
      parameter._dpar.push_back(atof(vs[1].c_str()));
      parameter._dpar.push_back(atof(vs[2].c_str()));
      parameter._dpar.push_back(atof(vs[3].c_str()));
      parameter._dpar.push_back(atof(vs[4].c_str()));
      if (EQn(vs[5].c_str(), "-", 1))
        parameter._ipar.push_back(0);
      else if (EQn(vs[5].c_str(), "D", 1))
        parameter._ipar.push_back(1);
      else if (EQn(vs[5].c_str(), "A", 1))
        parameter._ipar.push_back(2);
      _ffvdwparams.push_back(parameter);
    }

    if (ifs)
      ifs.close();

    return 0;
  }
