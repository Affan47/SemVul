absolute_name (std::string rel_name, std::string parent) const {
  std::cerr << "absolute_name ('" << rel_name << "', '" << parent << "')\n";
  if (parent[0] != '/')
    return rel_name;

  if (rel_name[0] == '/')
    {
      std::cerr << "  --> " << rel_name << "\n";
      return rel_name;
    }
  std::vector<std::string> path;
  uint dir_start = 1, dir_end;
  while (dir_start < parent.length())
    {
      dir_end = dir_start;
      while (dir_end < parent.length() && parent[dir_end] != '/')
        dir_end ++;
      path.push_back (parent.substr (dir_start, dir_end - dir_start));
      dir_start = dir_end + 1;
    }
  path.pop_back();
  dir_start = 0;
  std::string tmp;
  while (dir_start < rel_name.length())
    {
      dir_end = dir_start;
      while (dir_end < rel_name.length() && rel_name[dir_end] != '/')
        dir_end ++;
      tmp = rel_name.substr (dir_start, dir_end - dir_start);
      dir_start = dir_end + 1;
      if (tmp == ".")
        continue;
      else if (tmp == "..")
        path.pop_back();
      else
        path.push_back (tmp);
    }
  std::string rv;
  for (uint i = 0; i < path.size(); i ++)
    rv = rv + "/" + path[i];
  std::cerr << " ---> " << rv << "\n";
  return rv;
}
