score1() {
  UrlMap m;
  vector<string> v;
  v.push_back("fooboo/bar/baz");
  m.addPart("", md[0], v);
  m.dumpJigdoInfo();
  expectEnum(m[md[0]], "fooboo/bar/baz");
}
