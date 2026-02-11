ReadNext(std::string& line) {
  if(!fin) return false;
  current_section_changed=false;
  for(;;) {
    line=config_read_line(*fin);
    if(line=="") {
      current_section="";
      current_section_n=-1;
      current_section_p=section_names.end();
      current_section_changed=true;
      return true;
    };
    std::string::size_type n=line.find_first_not_of(" \t");
    if(n == std::string::npos) continue;
    if(line[n] == '[') {
      n++; std::string::size_type nn = line.find(']',n);
      if(nn == std::string::npos) { line=""; return false; };
      current_section=line.substr(n,nn-n);
      current_section_n=-1;
      current_section_p=section_names.end();
      current_section_changed=true;
      continue;
    };
    if(!section_names.empty()) {
      bool match = false;
      int s_n = -1;
      for(std::list<std::string>::iterator sec = section_names.begin();
                                       sec!=section_names.end();++sec) {
        std::string::size_type len = sec->length();
        s_n++;
        if(strncasecmp(sec->c_str(),current_section.c_str(),len) != 0) continue;
        if(len != current_section.length()) {
          if(current_section[len] != '/') continue;
        };
        current_section_n=s_n;
        current_section_p=sec;
        match=true; break;
      };
      if(!match) continue;
    };
    line.erase(0,n);
    break;
  };
  return true;
}
