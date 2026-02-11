findlines(std::ifstream& ifs, LineMap& values)
{
  ifs.seekg(0);
  std::string line;

  while(ifs) {
    if(getline(ifs, line)) {


      for(LineMap::iterator l = values.begin(); l != values.end(); ++l) {
        if(line.find(l->first) == 0) {
          l->second = line.substr(l->first.length()+1);
        }
      }
    }
  }
}
