toLower(const string& name) {


  if (name.find_first_not_of(" \n\t\v\b\r\f\a") == string::npos) return "";
  int firstChar = name.find_first_not_of(" \n\t\v\b\r\f\a");
  int lastChar  = name.find_last_not_of(" \n\t\v\b\r\f\a");
  string temp   = name.substr( firstChar, lastChar + 1 - firstChar);


  for (int i = 0; i < int(temp.length()); ++i) temp[i] = tolower(temp[i]);
  return temp;

}
