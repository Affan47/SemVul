skip_alpha(ifstream& fs)
  {
    string cline;
    while (!fs.eof()) {
      streampos curpos = fs.tellg();
      getline(fs,cline);
      cline += " ";
      istringstream ss(cline.c_str());
      string firstToken="";
      ss >> firstToken;
      if (isNumber(firstToken)) {
	if (!fs.eof()) { fs.seekg(curpos); } else { fs.clear(); fs.seekg(0,ios::beg); }
	return cline;
      }
    }
    return "";
  }
