summary() {
  ostringstream str;
  for (list<Summary>::const_iterator it = _global_warnings_summary.begin();
       it != _global_warnings_summary.end(); it++) {
    str << it->second << " times: " << it->first << endl;
  }
  return str.str();
}
