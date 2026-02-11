GetPath(const string& fileName) {
    string path = fileName.substr(0,MAX(int(fileName.find_last_of("\\")),int(fileName.find_last_of("/")))+1);
    if(path.empty()) { path = "./"; }
    return path;
  }
