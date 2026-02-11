str() {
  typedef set<pair<string, BasicBlock*> > ms;
  typedef map<string, ms> mm;
  typedef mm::iterator mm_iter;
  stringstream ss;

  for (mm_iter it = block->phis.begin(); it != block->phis.end(); it++) {
    string var = (*it).first;
    ms aux = (*it).second;

    ss << var << " = phi";

    for (ms::iterator pairs = aux.begin(); pairs != aux.end(); pairs++) {
      pair<string, BasicBlock*> p = (*pairs);
      ss << "[" << p.first << "," << p.second->str()   << "]";
    }
  }

  return ss.str();
}
