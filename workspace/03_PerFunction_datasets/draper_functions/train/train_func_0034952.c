kvu_string_to_int_vector(const string& str,
				     const string::value_type separator)
{
  vector<int> vec;
  string stmp = "";

  for(string::const_iterator p = str.begin(); p != str.end(); p++) {
    if (*p != separator)
      stmp += *p;
    else {
      if (stmp == "") continue;
      vec.push_back(atoi(stmp.c_str()));
      stmp = "";
    }
  }
  if (stmp.size() > 0)
    vec.push_back(atoi(stmp.c_str()));

  return vec;
}
