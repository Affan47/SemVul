ParseParamDef(std::string &filename)
  {
    vector<string> vs;
    char buffer[80];

    OBFFParameter parameter;


    ifstream ifs;
    if (OpenDatafile(ifs, filename).length() == 0) {
      obErrorLog.ThrowError(__FUNCTION__, "Cannot open mmffdef.par", obError);
      return false;
    }

    while (ifs.getline(buffer, 80)) {
      if (EQn(buffer, "*", 1)) continue;
      if (EQn(buffer, "$", 1)) continue;

      tokenize(vs, buffer);

      parameter.clear();
      parameter._ipar.push_back(atoi(vs[1].c_str()));
      parameter._ipar.push_back(atoi(vs[2].c_str()));
      parameter._ipar.push_back(atoi(vs[3].c_str()));
      parameter._ipar.push_back(atoi(vs[4].c_str()));
      parameter._ipar.push_back(atoi(vs[5].c_str()));
      _ffdefparams.push_back(parameter);
    }

    if (ifs)
      ifs.close();

    return 0;
  }
