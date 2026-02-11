Negate() {


  vector<RuneRange> v;
  v.reserve(ranges_.size() + 1);


  iterator it = begin();
  if (it == end()) {
    v.push_back(RuneRange(0, Runemax));
  } else {
    int nextlo = 0;
    if (it->lo == 0) {
      nextlo = it->hi + 1;
      ++it;
    }
    for (; it != end(); ++it) {
      v.push_back(RuneRange(nextlo, it->lo - 1));
      nextlo = it->hi + 1;
    }
    if (nextlo <= Runemax)
      v.push_back(RuneRange(nextlo, Runemax));
  }

  ranges_.clear();
  for (int i = 0; i < v.size(); i++)
    ranges_.insert(v[i]);

  upper_ = AlphaMask & ~upper_;
  lower_ = AlphaMask & ~lower_;
  nrunes_ = Runemax+1 - nrunes_;
}
