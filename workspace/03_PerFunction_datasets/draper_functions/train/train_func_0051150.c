ParseRDKitFormat(istringstream& ss, pattern& p)
  {


    const int dum = 20;
    string number, comment;
    getline(ss, number, ':');
    ss.ignore(dum, '\'');
    getline(ss, p.smartsstring, '\'');
    if(p.smartsstring[0]=='?')
      p.smartsstring="[999]";
    ss.ignore(dum,',');
    ss >> p.numoccurrences;
    ss.ignore(dum,'#');
    getline(ss, comment);


    Trim(comment);
    string::size_type pos;
    pos = comment.find("FIX");
    if(pos==string::npos)
      pos = comment.find("*NOTE*");
    if(pos!=string::npos)
      comment.erase(pos);
    p.description = number + ": " + comment;
    return true;
  }
