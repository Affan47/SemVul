ParseParamFile()
  {
    vector<string> vs;
    char buffer[BUFF_SIZE];


    ifstream ifs;
    if (OpenDatafile(ifs, "qeq.txt").length() == 0) {
      obErrorLog.ThrowError(__FUNCTION__, "Cannot open qeq.txt", obError);
      return;
    }


    obLocale.SetLocale();
    Vector3d P;
    float radius;
    while (ifs.getline(buffer, BUFF_SIZE)) {
      if (buffer[0] == '#')
        continue;

      tokenize(vs, buffer);
      if (vs.size() < 4)
        continue;


      radius = atof(vs[3].c_str())*Angstrom;
      P << atof(vs[1].c_str())*eV, atof(vs[2].c_str())*eV, 1.0/(radius*radius);
      _parameters.push_back(P);
    }
  }
