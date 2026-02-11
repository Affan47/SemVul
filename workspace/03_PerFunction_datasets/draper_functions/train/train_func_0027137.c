LoadIdx(const string & filename, set<string> & dic) {
    ifstream ifile(filename.c_str());
    if (!ifile) {
      cerr << "error: cannot open " << filename << endl;
      exit(1);
    }
    string line;
    while (getline(ifile, line)) {
      if (line[0] == ' ') continue;
      istringstream is(line);
      string base;
      is >> base;
      dic.insert(base);
      string base2(base);
      base2[0] = toupper(base[0]);
      dic.insert(base2);
    }
  }
