put () const {
  std::vector<unsigned long> v;
  v.push_back (engineIDulong<DRand48Engine>());
  unsigned short dummy[] = { 0, 0, 0 };
  unsigned short* cseed = seed48(dummy);
  for (int i=0; i<3; ++i) {
    dummy[i] = cseed[i];
    v.push_back (static_cast<unsigned long>(cseed[i]));
  }
  seed48(dummy);
  return v;
}
