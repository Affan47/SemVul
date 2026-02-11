get_word(std::string& s,std::string& word) {
  std::string::size_type w_s;
  std::string::size_type w_e;
  word.resize(0);
  w_s=s.find_first_not_of(" \t");
  if(w_s == std::string::npos) { s.resize(0); return; };
  if(s[w_s] == '\'') {
    w_e=s.find('\'',++w_s);
  } else if(s[w_s] == '"') {
    w_e=s.find('"',++w_s);
  } else {
    w_e=s.find_first_of(" \t",w_s);
  };
  if(w_e == std::string::npos) w_e=s.length();
  word=s.substr(w_s,w_e-w_s);
  if((s[w_e] == '\'') || (s[w_e] == '"')) ++w_e;
  w_s=s.find_first_not_of(" \t",w_e);
  if(w_s == std::string::npos) w_s=w_e;
  s=s.substr(w_s);
  return;
}
