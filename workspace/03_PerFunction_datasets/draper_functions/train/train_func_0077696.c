Planets() const {
  std::vector<Planet> r;
  for (int i = 0; i < planets_.size(); ++i) {
    const Planet& p = planets_[i];
    r.push_back(p);
  }
  return r;
}
