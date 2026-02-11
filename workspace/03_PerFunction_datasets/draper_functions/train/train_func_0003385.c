readString(string line, bool warn) {


  if (!isConstructed) return false;


  if (line.find_first_not_of(" \n\t\v\b\r\f\a") == string::npos) return true;


  int firstChar = line.find_first_not_of(" \n\t\v\b\r\f\a");
  if (!isalnum(line[firstChar])) return true;


  if (isdigit(line[firstChar]))
    return particleData.readString(line, warn);


  return settings.readString(line, warn);

}
