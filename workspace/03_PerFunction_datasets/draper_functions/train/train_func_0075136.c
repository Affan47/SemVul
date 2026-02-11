in_addrrange_list(stl_list(addrrange) &lst, _addr *a) {
  stl_list(addrrange)::iterator it = lst.begin();
  while (it != lst.end()) {
    if (addrrange_matches(it->range, a)) return true;
    it++;
  }
  return false;
}
