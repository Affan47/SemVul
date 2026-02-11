is_loop_end(string& lowline, string& line, string toplabel) {
    string::size_type pos,poslab;
    string label;


    if (! (line.size()) ) return false;

    pos = lowline.find_first_not_of(" \t");


    poslab=toplabel.find_first_not_of("0123456789");
    if((toplabel.size()>0) && (poslab==string::npos)) {

      poslab = pos;
      pos    = lowline.find_first_not_of("0123456789",pos);


      if(poslab==pos) return false;
      label=line.substr(poslab,pos-poslab);


      if (toplabel==label) return true;
      else                 return false;

    } else {

      if(lowline.compare(pos, 3, "end") != 0)
        return false;

      pos = lowline.find_first_not_of(" \t", pos+3);
      if(pos==string::npos) return false;

      if(lowline.compare(pos, 2, "do") != 0)
        return false;

      if(!(lowline[pos+2] == ' ' || lowline[pos+2] == '\t' || lowline[pos+2] == '\0'))
        return false;


      if(toplabel.size()) {


	poslab = lowline.find_first_not_of(" \t",pos+2);
	pos = lowline.find_first_of(" \t",poslab);
	if(poslab==pos) return false;
	label=line.substr(poslab,pos-poslab);


	if (toplabel==label) return true;
	else                 return false;

      } else {
	return true;
      }
    }
  }
