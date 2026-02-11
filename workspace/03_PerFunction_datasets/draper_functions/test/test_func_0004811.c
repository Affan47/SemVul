validate(const std::string& folder_name) {

  std::pair<bool, std::string> return_val;

  if (folder_name.find(PATH_DIVIDER) != std::string::npos) {
    return_val.first = false;
    return_val.second = gettext("Folder name cannot contain character: ");
    return_val.second += PATH_DIVIDER;
  }

  else {
    std::pair<std::set<std::string>::iterator, bool> result = folder_set.insert(folder_name);

    if ((return_val.first = result.second)) folder_set.erase(folder_name);
    else {
      return_val.second = gettext("The following folder already exists: ");
      return_val.second += folder_name;
    }
  }

  return return_val;
}
