real_name(std::string name) {
  std::string fname = "";
  if(mount.length() != 0) { fname+='/'+mount; };
  if(name.length() != 0) { fname+='/'+name; };
  return fname;
}
